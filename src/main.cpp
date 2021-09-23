#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <string>

bool debug = false;
bool silent = false;
int spam_times = 0;

static std::string readBuffer;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (std::string(argv[i]) == "--debug")
        {
            debug = true;
        }

        if (std::string(argv[i]) == "--silent")
        {
            silent = true;
        }

        if (std::string(argv[i]) == "--spam")
        {
            if (atoi(argv[i + 1]) > 1)
                spam_times = atoi(argv[i + 1]);
            else
                spam_times = 0;
        }

        // if (std::string(argv[i]) == "--agent")
        // {
        //     do
        //     {

        //     }
        // }
    }

    if (debug)
        printf("-- D -- cppofetch started\n");

    CURL *curl;
    struct curl_slist *headers = NULL;
    // CURLcode res;
    curl = curl_easy_init();

    if (curl)
    {
        if (debug)
            printf("-- D -- fetching %s\n", argv[1]);
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        if (spam_times > 1)
        {
            for (int i = 0; i < spam_times; i++)
            {
                curl_easy_perform(curl);
                if (!silent)
                    printf("%s\n", readBuffer.c_str());
            }
        }

        curl_easy_perform(curl);

        if (!silent)
            printf("%s\n", readBuffer.c_str());

        if (debug)
        {
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            printf("-- D -- status code %ld\n", http_code);
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}
