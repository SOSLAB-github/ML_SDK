/*
 * config_manager.h
 *
 *  Created on: Nov 13, 2018
 *      Author: gnohead
 */

#ifndef CONFIG_MANAGER_H_
#define CONFIG_MANAGER_H_

#include <string>
#include <vector>
#include <map>
#include <typeindex>

#include "soslab_typedef.h"

/**
 *  @brief SOSLAB APIs [ for standard C++11 ]
 *  @author gnohead
 *  @date 2018. 11.
 */
namespace SOSLAB {
    /**
     * @brief configuration file manager class
     */
    class SOSLAB_EXPORTS ConfigManager
    {
    private:
        /**
         * @brief single item
         */
        class SOSLAB_EXPORTS SingleItem
        {
        private:
            std::type_index data_type_;
            std::vector<INT_T> int_values_;
            std::vector<FLOAT_T> float_values_;
            std::vector<std::string> str_values_;

        public:
            /**
             * @brief constructor
             */
            SingleItem();
            ~SingleItem();

            /**
             * @brief get stored data type name
             * @return data type index
             */
            std::type_index data_type() const;

            /**
             * @brief clear item
             */
            void clear();

            /**
             * @brief get item vector
             * @param item [out]
             * @return success or failed
             */
            bool get(std::vector<INT_T>& item) const;
            bool get(std::vector<FLOAT_T>& item) const;
            bool get(std::vector<std::string>& item) const;

            /**
             * @brief set item vector (only for int / float / std::string type)
             * @param value [in]
             * @return success or failed
             */
            bool set(const std::vector<INT_T>& value);
            bool set(const std::vector<FLOAT_T>& value);
            bool set(const std::vector<std::string>& value);

        }; /* class SingleItem */

        /**
         * @brief item map type
         */
        typedef std::map<std::string, SingleItem> item_map_t;

        /**
         * @brief configuration data container
         *
         * section - item1 - value<item_t>
         *           item2 - value<item_t>
         */
        std::map<std::string,  item_map_t> data_map_;

    public:
        /**
         * @brief contructor
         */
        ConfigManager(const std::size_t float_precision = 10);
        ~ConfigManager();

        /**
         * @brief Printing configuration message to standard output
         * @return built(loaded) message line count;
         */
        std::size_t print_message();

        /**
         * @brief load configuration file
         * @param configuration file path
         */
        bool load(const char* filepath);

        /**
         * @brief save configuration file
         * @param configuration file path
         */
        bool save(const char* filepath);

        /**
         * @brief get configuration data
         * @param value list [out]
         * @param section name [in]
         * @param item name [in]
         * @return success or failed
         */
        template <typename T>
        bool get(std::vector<T>& value, const char* section, const char* item) const;

        /**
         * @brief set configuration data
         * @param value list [in]
         * @param section name [in]
         * @param item name [in]
         * @return success or failed
         */
        template <typename T>
        bool set(const std::vector<T>& value, const char* section, const char* item);

    private:
        /**
         * @brief Make human readable configuration message from internal data map
         * @return message line list
         */
        std::vector<std::string> build_configuration_message();

        std::size_t float_precision_;

    }; /* class ConfigParser */

} /* namespace SOSLAB */



#endif /* CONFIG_MANAGER_H_ */
