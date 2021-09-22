#include <stdio.h>
#include <curl/curl.h>
#include <iostream>

bool debug = false;

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (std::string(argv[i]) == "--debug")
        {
            debug = true;
        }
    }

    if (debug)
        printf("-- D -- cppofetch started\n");

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    if (curl)
    {
        if (debug)
            printf("-- D -- fetching %s\n", argv[1]);
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);

        if (debug)
            // TODO: not working?????
            printf("-- D -- status code %d\n", res);

        curl_easy_cleanup(curl);
    }

    return 0;
}
