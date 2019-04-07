#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

struct curl_fetch_st {
	char *payload;
	size_t size;
};

char *unescape(const char *original) {
	char *result;
	char *temp;

	/* Remove the quotes from the beginning and end */
	result = strndup(original+1, strlen(original)-2);

	temp = strchr(result, '\\');

	while(temp) {
		strcpy(temp, temp + 1);
		temp = strchr(result, '\\');
	}

	return result;
}

size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	/* calculate buffer size */
	size_t realsize = size * nmemb;
	/* cast pointer to fetch struct */
	struct curl_fetch_st *p = (struct curl_fetch_st *) userp;

	/* expand buffer */
	p->payload = (char *)realloc(p->payload, p->size + realsize + 1);

	if(p->payload == NULL) {
		/* this isn't good */
		fprintf(stderr, "Error: Failed to expand buffer in curl_callback");
		free(p->payload);
		return -1;
	}

	memcpy(&(p->payload[p->size]), contents, realsize);
	p->size += realsize;
	p->payload[p->size] = 0;
	return realsize;
}

CURLcode curl_fetch_url(CURL *ch, const char *url, struct curl_fetch_st *fetch)
{
	CURLcode rcode;
	fetch->payload = (char *)calloc(1, sizeof(fetch->payload));

	if(fetch->payload == NULL) {
		fprintf(stderr, "Error: Faild to allocate payload in curl_fetch_url");
		return CURLE_FAILED_INIT;
	}

	fetch->size = 0;
	curl_easy_setopt(ch, CURLOPT_URL, url);
	curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, curl_callback);
	curl_easy_setopt(ch, CURLOPT_WRITEDATA, (void *)fetch);
	curl_easy_setopt(ch, CURLOPT_USERAGENT, "stscript/1.0");
	curl_easy_setopt(ch, CURLOPT_TIMEOUT, 5);
	curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(ch, CURLOPT_MAXREDIRS, 1);

	rcode = curl_easy_perform(ch);

	return rcode;
}

/* Return a random number between 0 and limit-1 */
int rand_lim(int limit) {
	return rand() / (RAND_MAX / limit + 1);
}

int main(int argc, char **argv)
{
	CURL *ch;
	CURLcode rcode;

	struct json_object *json;
	enum json_tokener_error jerr = json_tokener_success;

	struct curl_fetch_st curl_fetch;
	struct curl_fetch_st *cf = &curl_fetch;
	struct curl_slist *headers = NULL;

	struct json_object *tmp;
	struct json_object *tmp2;
	struct json_object *tmparr;
	int i;
	char *title;

	char *url = "https://www.reddit.com/r/showerthoughts/hot.json?limit=100";

	srand(time(NULL));

	if((ch = curl_easy_init()) == NULL) {
		fprintf(stderr, "Error: Failed to create curl handle in fetch_session");
		return 1;
	}

	headers = curl_slist_append(headers, "Accept: application/json");
	headers = curl_slist_append(headers, "Content-Type: application/json");

	curl_easy_setopt(ch, CURLOPT_CUSTOMREQUEST, "GET");
	curl_easy_setopt(ch, CURLOPT_HTTPHEADER, headers);

	rcode = curl_fetch_url(ch, url, cf);

	curl_easy_cleanup(ch);
	curl_slist_free_all(headers);

	if(rcode != CURLE_OK || cf->size < 1) {
		fprintf(stderr, "Error: Failed to fetch url (%s) - curl said: %s",
			url, curl_easy_strerror(rcode));
		return 2;
	}

	if(cf->payload == NULL) {
		fprintf(stderr, "Error: Failed to populate payload");
		return 3;
	}

	json = json_tokener_parse_verbose(cf->payload, &jerr);
	free(cf->payload);
	if(jerr != json_tokener_success) {
		fprintf(stderr, "Error: Failed to parse json string");
		json_object_put(json);
		return 4;
	}

	/* Drill down to the nodes that have what we want */
	json_object_object_get_ex(json, "data", &tmp);
	json_object_object_get_ex(tmp, "children", &tmparr);

	/* Fill an array with thoughts */
	const char *titles[json_object_array_length(tmparr)];
	for(i = 0; i < json_object_array_length(tmparr); i++) {
		tmp = json_object_array_get_idx(tmparr, i);
		json_object_object_get_ex(tmp, "data", &tmp2);
		json_object_object_get_ex(tmp2, "title", &tmp2);

		titles[i] = json_object_to_json_string(tmp2);
	}

	/* Pick 1 to print out to the screen */
	title = unescape(titles[rand_lim(json_object_array_length(tmparr))]);
	printf("%s\n", title);
	free(title);

	json_object_put(json);

	return 0;
}
