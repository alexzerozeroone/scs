#include <stdio.h>
#include <curl/curl.h>
// #include "iostream"
#include <algorithm>
#include <string>

bool debug = false;
bool follow = true;
bool silent = false;
bool help = false;

int spam_times = 0;

std::string method = "GET";
std::string url = "";

// I am an epic fail for not making this work - azzo
// std::string user_agent;
// std::string auth;

// debug prefix
std::string debug_prefix = "//";
const char *prefix = debug_prefix.c_str();

static std::string readBuffer;

bool whitespace(std::string s)
{
    if (s.empty())
    {
        return true;
    }

    return false;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

void eraseAllSS(std::string &mainStr, const std::string &toErase)
{
    size_t pos = std::string::npos;
    while ((pos = mainStr.find(toErase)) != std::string::npos)
    {
        mainStr.erase(pos, toErase.length());
    }
}

// soon:tm:
// void debugf(char *text, ...) {
//     printf(text);
// }

// string to lower function
std::string toLower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

int main(int argc, char **argv)
{
    if (argc == 1) // no arguments
    {
        help = true;
    }

    for (int i = 0; i < argc; i++)
    {
        if (toLower(std::string(argv[i])) == "--help")
        {
            help = true;
        }

        else if (toLower(std::string(argv[i])) == "--debug")
        {
            debug = true;
        }

        else if (toLower(std::string(argv[i])) == "--silent")
        {
            silent = true;
        }

        else if (toLower(std::string(argv[i])) == "--flood")
        {
            if (atoi(argv[i + 1]) > 1)
                spam_times = atoi(argv[i + 1]);
            else
                spam_times = 0;
        }

        else if (toLower(std::string(argv[i])) == "--follow")
        {
            int v = argc;
            if (v++ < argc)
                if (atoi(argv[i + 1]) == 0)
                    follow = false;
                else
                    follow = true;
        }

        else if (toLower(std::string(argv[i])) == "--method")
        {
            method = std::string(argv[i + 1]);
        }

        else if (toLower(std::string(argv[i])) == "--url")
        {
            url = std::string(argv[i + 1]);
        }
    }

    if (help)
    {
        printf(
            "Usage: scs [arguments]\n\n"
            "Argument list:\n"
            "\t--url <url>\t\tSet the url to use. (REQUIRED)\n"
            "\t--debug\t\t\tPrint debug information.\n"
            "\t--silent\t\tDoesn't output result returned. (Works well with --debug)\n"
            "\t--flood <times>\t\tFlood enter request the url <times> times\n"
            "\t--follow <0/1>\t\tFollow the link chain. (0 for don't follow, 1 for follow\n"
            "\t--method <method>\tSet the method to use. (e.g GET)\n"
            "\t--help\t\t\tPrint this help message.\n"
            "\n"
            "");

        return 0;
    }

    if (debug)
    {
        printf("%s scs started\n", prefix);
        printf("%s Debug boolean is 1\n", prefix);
    }

    CURL *curl;
    // struct curl_slist *headers = NULL;
    // CURLcode res;
    curl = curl_easy_init();

    if (curl)
    {
        if (whitespace(url))
        {
            printf("%s No URL specified\n", prefix);
            return 1;
        }

        if (debug && follow)
        {
            printf("%s Follow location boolean set to %d\n", prefix, follow);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        }

        else
        {
            follow = 0L;
            if (debug)
                printf("%s Follow location boolean set to %d\n", prefix, follow);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
        }

        if (debug && silent)
            printf("%s Silent boolean set to %d\n", prefix, silent);

        if (!whitespace(method) && debug)
            printf("%s Request method string set to %s\n", prefix, method.c_str());

        if (debug && spam_times > 1)
            printf("%s Flood times integer set to %d\n", prefix, spam_times);

        if (debug)
            printf("%s Fetching link %s\n", prefix, url.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, follow);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

        curl_easy_setopt(curl, CURLOPT_USERAGENT, "scs/1.2.3.4");

        if (!whitespace(method))
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());

        if (1 > spam_times)
            curl_easy_perform(curl);

        if (!silent)
        {
            printf("%s", readBuffer.c_str());
        }

        long http_code = 0;
        double elapsed;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);

        if (debug && !(spam_times > 1))
        {
            printf("%s Result returned status code %ld\n", prefix, http_code);
        }

        // currently acting weird
        // if (http_code == 0)
        // {
        //     if (debug)
        //         printf("%s Host does not exist or an error occured\n", prefix);
        // }

        if (spam_times > 1)
        {
            for (int i = 0; i < spam_times; i++)
            {
                curl_easy_perform(curl);

                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
                curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);

                if (!silent)
                    printf("%s\n", readBuffer.c_str());

                if (debug)
                {
                    long http_code = 0;
                    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
                    printf("%s Result returned status code %ld\n", prefix, http_code);
                    printf("%s Time elapsed %fs\n", prefix, elapsed);
                    printf("%d requests left\n", spam_times - i);
                }

                readBuffer = "";
            }
        }

        // if (elapsed > 10)
        // {
        //     if (debug)
        //         printf("%s Connection timed out\n", prefix);
        // }

        if (debug && spam_times < 1)
            printf("%s Time elapsed %fs\n", prefix, elapsed);

        if (debug)
            printf("%s scs ended\n", prefix);
        curl_easy_cleanup(curl);
    }

    return 0;
}
