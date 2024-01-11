#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Info.hpp>
#include <sstream>
#include <thread>

using namespace curlpp::options;

void clear() {
    #if defined _WIN32
        system("cls");
        //clrscr(); // including header file : conio.h
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
    #elif defined (__APPLE__)
        system("clear");
    #endif
}

int pinger(const std::string & url) {
    try {
        //curlpp::Cleanup myCleanup;
        curlpp::Easy handle;
        handle.setOpt<Url>(url);
        // disable printing to stdout
        std::ostringstream os;
        WriteStream writeStream(&os);
        handle.setOpt(writeStream);
        // timeout after 1 second
        handle.setOpt<ConnectTimeout>(1);
        handle.setOpt<Timeout>(1);
        handle.perform();
        int responseCode;
        curlpp::InfoTypeConverter<int>::get(handle, CURLINFO_RESPONSE_CODE, responseCode);
        return responseCode;
    }
    catch(curlpp::RuntimeError & e)
    {
        //std::cout << e.what() << std::endl;
        return 0;
    }

    catch(curlpp::LogicError & e)
    {
        //std::cout << e.what() << std::endl;
        return 0;
    }
}

int main()
{

    std::vector<std::string> urls = {"https://www.fit.cvut.cz", "https://kos.cvut.cz", "https://courses.fit.cvut.cz",
                                     "https://online.fit.cvut.cz", "https://marast.fit.cvut.cz", "https://timetable.fit.cvut.cz",
                                     "https://progtest.fit.cvut.cz", "https://dbs.fit.cvut.cz", "https://profile.fit.cvut.cz",
                                     "https://grades.fit.cvut.cz", "https://auth.fit.cvut.cz", "https://gitlab.fit.cvut.cz",
                                     "https://fit-wiki.cz", "https://houdeda2.cz"};

    //store previous state of ping results for each url in time

    const int backlogSize = 20;
    std::vector<std::vector<bool>> results;
    results.assign(urls.size(), std::vector<bool>(backlogSize));


    // purple: \033[1;35m
    std::cout << "\033[0;32m";
    // print urls with indexes
    while(true) {

        for(int i = 0; i < urls.size(); ++i) {
            int value = pinger(urls[i]);

            bool isOk = false;
            if (value == 200 || value == 301 || value == 302 || value == 303) {
                isOk = true;
            }

            // add result to backlog
            results[i].insert(results[i].begin(), isOk);
            // remove oldest result from backlog if bigger than backlog size

            if (results[i].size() > backlogSize) {
                results[i].pop_back();
            }
        }

        clear();

        std::cout << "┏━━┳━━━━ << URLS >> ━━━━━━━━━━━━━━━━━┓" << std::endl;
        for (int i = 0; i < urls.size(); i++) {
            std::cout << "\033[0;32m";

            std::cout << "┃";
            if (i < 10)/* index is one digit*/ {
                std::cout << i << " ┃ " << urls[i];
                // dynamically add spaces to align urls
                for (int j = 0; j < 32 - urls[i].length(); j++) {
                    std::cout << " ";
                }
            } else {
                std::cout << i << "┃ " << urls[i];

                // dynamically add spaces to align urls
                for (int j = 0; j < 32 - urls[i].length(); j++) {
                    std::cout << " ";
                }
            }
            std::cout << "┃";



            // print backlog
            for (auto result: results[i]) {
                if (result) {
                    std::cout << "\033[1;32m ┃\033[0m";
                } else {
                    std::cout << "\033[1;31m ┃\033[0m";
                }
            }

            std::cout << std::endl;

        }
        std::cout << "\033[0;32m┗━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    // print indexes above returned values

    std::cout << "┏━━━━━━━ << PING RESULTS >> ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
                 "┃ Indexes:                                                                        ┃\n"
                 "┣━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┳━┳━━━┫\n"
                 "┃ \033[1;35m0\033[0;32m ┃ ┃ \033[1;35m1\033[0;32m ┃ ┃ \033[1;35m2\033[0;32m ┃ ┃ \033[1;35m3\033[0;32m ┃ ┃ \033[1;35m4\033[0;32m ┃ ┃ \033[1;35m5\033[0;32m ┃ ┃ \033[1;35m6\033[0;32m ┃ ┃ \033[1;35m7\033[0;32m ┃ "
                 "┃ \033[1;35m8\033[0;32m ┃ ┃ \033[1;35m9\033[0;32m ┃ ┃ \033[1;35m10\033[0;32m┃ ┃ \033[1;35m11\033[0;32m┃ ┃ \033[1;35m12\033[0;32m┃ ┃ \033[1;35m13\033[0;32m┃" << std::endl;


    while (true) {
        for(auto & url : urls) {
            int value = pinger(url);
            //std::cout << "Response code from " + url +  ": ";
            if (value == 200 || value == 301 || value == 302 || value == 303) {
                //std::cout << "\033[1;32m" << value << "\033[0m" << std::endl;
                std::cout << "\033[1;32m┃" << value << "┃ \033[0m";
            } else {
                //std::cout << "\033[1;31m" << value << "\033[0m" << std::endl;
                if ( value == 0)
                    std::cout << "\033[1;31m┃" << " X " << "┃ \033[0m";
                else
                std::cout << "\033[1;31m┃" << value << "┃ \033[0m";
            }
            std::cout.flush();
        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }





    //return 0;
}
