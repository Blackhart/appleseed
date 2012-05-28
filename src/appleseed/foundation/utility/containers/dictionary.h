
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2012 Francois Beaune, Jupiter Jazz Limited
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_FOUNDATION_UTILITY_CONTAINERS_DICTIONARY_H
#define APPLESEED_FOUNDATION_UTILITY_CONTAINERS_DICTIONARY_H

// appleseed.foundation headers.
#include "foundation/core/exceptions/stringexception.h"
#include "foundation/utility/string.h"

// Standard headers.
#include <cstddef>
#include <string>

// Forward declarations.
namespace foundation    { class Dictionary; }

//
// On Windows, define FOUNDATIONDLL to __declspec(dllexport) when building the DLL
// and to __declspec(dllimport) when building an application using the DLL.
// Other platforms don't use this export mechanism and the symbol FOUNDATIONDLL is
// defined to evaluate to nothing.
//

#ifndef FOUNDATIONDLL
#ifdef _WIN32
#ifdef APPLESEED_FOUNDATION_EXPORTS
#define FOUNDATIONDLL __declspec(dllexport)
#else
#define FOUNDATIONDLL __declspec(dllimport)
#endif
#else
#define FOUNDATIONDLL
#endif
#endif

namespace foundation
{

//
// The exception thrown when accessing a dictionary item that does not exist.
//

struct ExceptionDictionaryItemNotFound
  : public StringException
{
    explicit ExceptionDictionaryItemNotFound(const char* key)
      : StringException("dictionary item not found", key)
    {
    }
};


//
// A string-to-string dictionary that can cross DLL boundaries.
//

class FOUNDATIONDLL StringDictionary
{
  public:
    class FOUNDATIONDLL const_iterator
    {
      public:
        // Value type.
        typedef const_iterator value_type;

        // Constructors.
        const_iterator();
        const_iterator(const const_iterator& rhs);

        // Destructor.
        ~const_iterator();
        
        // Assignment operator.
        const_iterator& operator=(const const_iterator& rhs);

        // Equality and inequality tests.
        bool operator==(const const_iterator& rhs) const;
        bool operator!=(const const_iterator& rhs) const;

        // Preincrement and predecrement operators.
        const_iterator& operator++();
        const_iterator& operator--();

        // Dereference operator.
        const value_type& operator*() const;

        // Get the name of this item.
        const char* name() const;

        // Get the value of this item.
        const char* value() const;
        template <typename T> T value() const;

      private:
        friend class StringDictionary;

        struct Impl;
        Impl* impl;
    };

    // Constructors.
    StringDictionary();
    StringDictionary(const StringDictionary& rhs);

    // Destructor.
    ~StringDictionary();

    // Assignment operator.
    StringDictionary& operator=(const StringDictionary& rhs);

    // Return the number of items in the dictionary.
    size_t size() const;

    // Return true if the dictionary is empty.
    bool empty() const;

    // Remove all items from the dictionary.
    void clear();

    // Insert an item into the dictionary.
    StringDictionary& insert(const char* key, const char* value);
    template <typename T> StringDictionary& insert(const char* key, const T& value);
    template <typename T> StringDictionary& insert(const std::string& key, const T& value);

    // Return true if an item with a given name exists in the dictionary.
    bool exist(const char* key) const;
    template <typename T> bool exist(const std::basic_string<T>& key) const;

    // Retrieve an item from the dictionary.
    // Throws a ExceptionDictionaryItemNotFound exception if the item could not be found.
    const char* get(const char* key) const;
    template <typename T> T get(const char* key) const;
    template <typename T> T get(const std::string& key) const;

    // Remove an item from the dictionary, if it exists.
    StringDictionary& remove(const char* key);
    template <typename T> StringDictionary& remove(const std::basic_string<T>& key);

    const_iterator begin() const;
    const_iterator end() const;

  private:
    struct Impl;
    Impl* impl;
};


//
// A string-to-dictionary dictionary that can cross DLL boundaries.
//

class FOUNDATIONDLL DictionaryDictionary
{
  public:
    class FOUNDATIONDLL const_iterator
    {
      public:
        // Value type.
        typedef const_iterator value_type;

        // Constructors.
        const_iterator();
        const_iterator(const const_iterator& rhs);

        // Destructor.
        ~const_iterator();

        // Assignment operator.
        const_iterator& operator=(const const_iterator& rhs);

        // Equality and inequality tests.
        bool operator==(const const_iterator& rhs) const;
        bool operator!=(const const_iterator& rhs) const;

        // Preincrement and predecrement operators.
        const_iterator& operator++();
        const_iterator& operator--();

        // Dereference operator.
        const value_type& operator*() const;

        // Get the name of this item.
        const char* name() const;

        // Get the value of this item.
        const Dictionary& value() const;

      private:
        friend class DictionaryDictionary;

        struct Impl;
        Impl* impl;
    };

    // Constructors.
    DictionaryDictionary();
    DictionaryDictionary(const DictionaryDictionary& rhs);

    // Destructor.
    ~DictionaryDictionary();

    // Assignment operator.
    DictionaryDictionary& operator=(const DictionaryDictionary& rhs);

    // Return the number of items in the dictionary.
    size_t size() const;

    // Return true if the dictionary is empty.
    bool empty() const;

    // Remove all items from the dictionary.
    void clear();

    // Insert an item into the dictionary.
    DictionaryDictionary& insert(const char* key, const Dictionary& value);
    template <typename T> DictionaryDictionary& insert(
        const std::basic_string<T>& key,
        const Dictionary&           value);

    // Return true if an item with a given name exists in the dictionary.
    bool exist(const char* key) const;
    template <typename T> bool exist(const std::basic_string<T>& key) const;

    // Retrieve an item from the dictionary.
    // Throws a ExceptionDictionaryItemNotFound exception if the item could not be found.
    Dictionary& get(const char* key);
    const Dictionary& get(const char* key) const;
    template <typename T> Dictionary& get(const std::basic_string<T>& key);
    template <typename T> const Dictionary& get(const std::basic_string<T>& key) const;

    // Remove an item from the dictionary, if it exists.
    DictionaryDictionary& remove(const char* key);
    template <typename T> DictionaryDictionary& remove(const std::basic_string<T>& key);

    const_iterator begin() const;
    const_iterator end() const;

  private:
    struct Impl;
    Impl* impl;
};


//
// A dictionary that supports nesting and that can cross DLL boundaries.
//

class FOUNDATIONDLL Dictionary
{
  public:
    // Return the number of items in the dictionary.
    size_t size() const;

    // Return true if the dictionary is empty.
    bool empty() const;

    // Remove all items from the dictionary.
    void clear();

    // Insert an item into the dictionary.
    Dictionary& insert(const char* key, const char* value);
    template <typename T> Dictionary& insert(const char* key, const T& value);
    template <typename T> Dictionary& insert(const std::string& key, const T& value);

    // Retrieve a string item from the dictionary.
    // Throws a ExceptionDictionaryItemNotFound exception if the item could not be found.
    const char* get(const char* key) const;
    template <typename T> T get(const char* key) const;
    template <typename T> T get(const std::string& key) const;

    // Access a child dictionary.
    // Throws a ExceptionDictionaryItemNotFound exception if the item could not be found.
    Dictionary& dictionary(const char* key);
    const Dictionary& dictionary(const char* key) const;
    template <typename T> Dictionary& dictionary(const std::basic_string<T>& key);
    template <typename T> const Dictionary& dictionary(const std::basic_string<T>& key) const;

    // Access the string dictionary.
    StringDictionary& strings();
    const StringDictionary& strings() const;

    // Access the dictionary dictionary.
    DictionaryDictionary& dictionaries();
    const DictionaryDictionary& dictionaries() const;

  private:
    StringDictionary        m_strings;
    DictionaryDictionary    m_dictionaries;
};


//
// StringDictionary::const_iterator class implementation.
//

template <typename T>
inline T StringDictionary::const_iterator::value() const
{
    return from_string<T>(value());
}


//
// StringDictionary class implementation.
//

template <typename T>
inline StringDictionary& StringDictionary::insert(const char* key, const T& value)
{
    return insert(key, to_string(value).c_str());
}

template <typename T>
inline StringDictionary& StringDictionary::insert(const std::string& key, const T& value)
{
    return insert(key.c_str(), value);
}

template <typename T>
inline bool StringDictionary::exist(const std::basic_string<T>& key) const
{
    return exist(key.c_str());
}

template <typename T>
inline T StringDictionary::get(const char* key) const
{
    return from_string<T>(get(key));
}

template <typename T>
inline T StringDictionary::get(const std::string& key) const
{
    return get<T>(key.c_str());
}

template <typename T>
inline StringDictionary& StringDictionary::remove(const std::basic_string<T>& key)
{
    return remove(key.c_str());
}


//
// DictionaryDictionary class implementation.
//

template <typename T>
inline DictionaryDictionary& DictionaryDictionary::insert(
    const std::basic_string<T>& key,
    const Dictionary&           value)
{
    return insert(key.c_str(), value);
}

template <typename T>
inline bool DictionaryDictionary::exist(const std::basic_string<T>& key) const
{
    return exist(key.c_str());
}

template <typename T>
inline Dictionary& DictionaryDictionary::get(const std::basic_string<T>& key)
{
    return get(key.c_str());
}

template <typename T>
inline const Dictionary& DictionaryDictionary::get(const std::basic_string<T>& key) const
{
    return get(key.c_str());
}

template <typename T>
inline DictionaryDictionary& DictionaryDictionary::remove(const std::basic_string<T>& key)
{
    return remove(key.c_str());
}


//
// Dictionary class implementation.
//

inline size_t Dictionary::size() const
{
    return m_strings.size() + m_dictionaries.size();
}

inline bool Dictionary::empty() const
{
    return m_strings.empty() && m_dictionaries.empty();
}

inline void Dictionary::clear()
{
    m_strings.clear();
    m_dictionaries.clear();
}

inline Dictionary& Dictionary::insert(const char* key, const char* value)
{
    m_strings.insert(key, value);
    return *this;
}

template <typename T>
inline Dictionary& Dictionary::insert(const char* key, const T& value)
{
    return insert(key, to_string(value).c_str());
}

template <>
inline Dictionary& Dictionary::insert(const char* key, const Dictionary& value)
{
    m_dictionaries.insert(key, value);
    return *this;
}

template <typename T>
inline Dictionary& Dictionary::insert(const std::string& key, const T& value)
{
    return insert(key.c_str(), value);
}

inline const char* Dictionary::get(const char* key) const
{
    return m_strings.get(key);
}

template <typename T>
inline T Dictionary::get(const char* key) const
{
    return m_strings.get<T>(key);
}

template <typename T>
inline T Dictionary::get(const std::string& key) const
{
    return m_strings.get<T>(key);
}

inline Dictionary& Dictionary::dictionary(const char* key)
{
    return m_dictionaries.get(key);
}

inline const Dictionary& Dictionary::dictionary(const char* key) const
{
    return m_dictionaries.get(key);
}

template <typename T>
inline Dictionary& Dictionary::dictionary(const std::basic_string<T>& key)
{
    return m_dictionaries.get(key.c_str());
}

template <typename T>
inline const Dictionary& Dictionary::dictionary(const std::basic_string<T>& key) const
{
    return m_dictionaries.get(key.c_str());
}

inline StringDictionary& Dictionary::strings()
{
    return m_strings;
}

inline const StringDictionary& Dictionary::strings() const
{
    return m_strings;
}

inline DictionaryDictionary& Dictionary::dictionaries()
{
    return m_dictionaries;
}

inline const DictionaryDictionary& Dictionary::dictionaries() const
{
    return m_dictionaries;
}

}       // namespace foundation

#endif  // !APPLESEED_FOUNDATION_UTILITY_CONTAINERS_DICTIONARY_H
