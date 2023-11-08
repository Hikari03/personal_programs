#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Info.hpp>
#include <sstream>

using namespace curlpp::options;

int pinger(const std::string & url) {
    //curlpp::Cleanup myCleanup;
    curlpp::Easy handle;
    handle.setOpt<Url>(url);
    // disable printing to stdout
    std::ostringstream os;
    WriteStream writeStream(&os);
    handle.setOpt(writeStream);
    handle.perform();
    int responseCode;
    curlpp::InfoTypeConverter<int>::get(handle, CURLINFO_RESPONSE_CODE, responseCode);
    return responseCode;
}

int main()
{
  try
  {
    int value = pinger("https://online.fit.cvut.cz/");

    std::cout << "Response code: " << value << std::endl;


    
  }

  catch(curlpp::RuntimeError & e)
  {
    std::cout << e.what() << std::endl;
  }

  catch(curlpp::LogicError & e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}