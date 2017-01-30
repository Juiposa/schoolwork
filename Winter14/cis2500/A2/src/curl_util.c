#include "morsecode.h"


/*this is the only function you need to use from this set of utilities.  
the other functions are helpping functions */

char* makeCurlCall(char* url, char* parameters) 
{
	CURL* curlData;
	BufferData buffer;
	CURLcode response;

	/* Initialize the buffer */
	buffer.string = malloc(sizeof(char));
	buffer.string[0] = '\0';
	buffer.length = 0;
	curlData = initializeCurlCall(url, parameters, &buffer);

	/* On first call initialize the CurlData buffer and make the POST */
	response = curl_easy_perform(curlData);
	if (response != CURLE_OK) 
	{
		return NULL;
	}
	/* Clean up curl stuff */
	curl_easy_cleanup(curlData);
	return buffer.string;
}

/*everything from here down in this file are helper functions that you do not need to call */

size_t processPost(void* stream, size_t size, size_t numberOfMembers, BufferData* buffer) 
{
	/* Reallocate the CurlData buffer to fit the extra data */
	size_t newLength = buffer->length + size*numberOfMembers;
	buffer->string = realloc(buffer->string, newLength+1);
	if (buffer->string == NULL) 
	{
		fprintf(stderr, "Failed to get data\n");
		exit(EXIT_FAILURE);
	}

	/* Copy the data to the CurlData buffer and update its length */
	memcpy(buffer->string + buffer->length, stream, size*numberOfMembers);
	buffer->string[newLength] = '\0';
	buffer->length = newLength;
        return size*numberOfMembers;
}


CURL* initializeCurlCall(char* url, char* parameters, BufferData* buffer) 
{
	CURL* curlData;

	/* Initialize the curl options */
	curlData = curl_easy_init();
    curl_easy_setopt(curlData, CURLOPT_URL, url);
    curl_easy_setopt(curlData, CURLOPT_POSTFIELDS, parameters);
    curl_easy_setopt(curlData, CURLOPT_WRITEFUNCTION, processPost);
    curl_easy_setopt(curlData, CURLOPT_WRITEDATA, buffer);

	return curlData;
}



