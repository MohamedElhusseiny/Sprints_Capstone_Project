/**
 * @file boost_logger.cpp
 * @author mohamed ahmed elhusseiny
 * @brief
 * @version 0.1
 * @date 2023-08-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "logger.hpp"
#include <boost/log/expressions.hpp>
#include <boost/log/attributes/counter.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sinks/text_file_backend.hpp>


namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;

void init_logging() 
{
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");
    logging::core::get()->add_global_attribute("LineID", attrs::counter<int>(1));
    logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());

    logging::add_file_log(
        logging::keywords::file_name = FILE_NAME,                           /* Absolute path with timestamp-based filename */
        logging::keywords::rotation_size = 1024,                            /* 1 KB rotation size */
        logging::keywords::format = "[%TimeStamp%] [%LineID%] [%Severity%] %Message%",        logging::keywords::auto_flush = true,                               /* Enable auto-flushing */ 
        logging::keywords::open_mode = std::ios_base::app,                  /* enable append */
        logging::keywords::target = "/tmp/daemon_logs/"                     /* dir for rotated files */
    );
    
    logging::core::get()->set_filter(
        logging::trivial::severity >= SEVERITY_THRESHOLD
    );
    LOG_INFO << "Logging setup completed successfully.";

}