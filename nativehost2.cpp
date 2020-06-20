#include <iostream>
#include <string>

std::string QUOTE = "\"";

void sendResponse(std::string pMsg);

int main(){
    std::string oneLine = "";

    // THIS CODE IS PREPARED FOR TEMPLATE ONLY
    // TO INTEGRATE WITH BARCODE THE DEVELOPMENTS REQUIRED

    // WARNING
    // DONT SEND A MESSAGE HERE IT CAUSES COMMUNICATION PROBLEM WITH CHROME EXTENSION
    // >>> Error: Error when communicating with the native messaging host. <<<
    // std::cout << "app is starting";

    // Other Errors Encountered
    //
    // >>> Specified host not found <<<<
    // Make sure the native messaging host json file is put under chrom folder and restart chrome (linux + osx)
    // for windows, it is the registry
    // 

    // DON'T
    // std::cout << "app is starting";

    while (1)
    {
        unsigned int length = 0;

        //read the first four bytes (=> Length)
        /*for (int i = 0; i < 4; i++)
        {
            int read_char = getchar();
            length += read_char * (int) pow(2.0, i*8);
            std::string s = std::to_string((long long)read_char) + "\n";
            fwrite(s.c_str(), sizeof(char), s.size(), f);
            fflush(f);
        }*/

        //Neat way!
        for (int i = 0; i < 4; i++)
        {
            unsigned int read_char = getchar();
            length = length | (read_char << i*8);
        }

        //read the json-message
        std::string msg = "";
        for (int i = 0; i < length; i++)
        {
            msg += getchar();
        }

        std::string message = "{\"text\":\"This is a response message\"}";
        // Collect the length of the message
        unsigned int len = message.length();

        // Now we can output our message
        if (msg == "{\"text\":\"#STOP#\"}"){
            message = "{\"text\":\"EXITING...\"}";
            len = message.length();

            std::cout   << char(len>>0)
                        << char(len>>8)
                        << char(len>>16)
                        << char(len>>24);

            std::cout << message;
            break;
        }

        std::string resp = "This is a response message from Native Host (v2)";
        /*
        std::string resp = msg;
        resp.replace(resp.begin(), resp.end(), "{", "*");
        resp.replace(resp.begin(), resp.end(), "}", "*");
        resp.replace(resp.begin(), resp.end(), ":", "-");
        resp.replace(resp.begin(), resp.end(), "\"", ".");
        */
        //resp = resp  + " incoming: " + msg;
        
        sendResponse(resp);

        /*
        std::string resp = "{\"text\":\"This is a response message from Native Host\"}";
        //std::string resp = "This is a response message from Native Host";
        unsigned int len2 = resp.length();
        std::cout   << char(len2>>0)
                    << char(len2>>8)
                    << char(len2>>16)
                    << char(len2>>24);
        std::cout << resp << std::flush;
        */
        /*
        len = length;
        std::cout   << char(len>>0)
                    << char(len>>8)
                    << char(len>>16)
                    << char(len>>24);

        //msg = "{text:\"RECEIPT\"}";
        std::cout << msg << std::flush;
        //std::cout << message << std::flush;
        */
    }


    return 0;
}


void sendResponse(std::string pMsg)
{
    //std::string resp = "{\"text\":\"This is a response message from Native Host\"}";
    std::string resp = "{" + QUOTE + "text" + QUOTE + ":" + QUOTE + pMsg + QUOTE + "}";

    //std::string resp = "This is a response message from Native Host";
    unsigned int len2 = resp.length();
    std::cout   << char(len2>>0)
                << char(len2>>8)
                << char(len2>>16)
                << char(len2>>24);
    std::cout << resp << std::flush;
}
