/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#ifndef _NGS_MESSAGE_H_
#define _NGS_MESSAGE_H_

#include "ngs/memory.h"
#include <google/protobuf/message.h>

namespace ngs
{

#ifdef USE_MYSQLX_FULL_PROTO
  typedef ::google::protobuf::Message Message;
#else
  typedef ::google::protobuf::MessageLite Message;
#endif

  /* X protocol client request object.

  This object provides a high-level interface for a X protocol object.
  The original network packet buffer, a parsed protobuf message or both can be
  held by it.

  The goal is to allow lazy parsing of messages, so that for example,
  a very large opaque field won't be copied into another buffer by protobuf.
  */
  class Request
  {
  public:
    Request(int8_t type)
    : m_type(type), m_message(NULL), m_owns_message(false) {}

    ~Request()
    {
      if (m_owns_message)
        delete m_message;
    }

    void set_parsed_message(Message *message, bool free_on_delete)
    {
      if (m_message && m_owns_message)
        delete m_message;
      m_message = message;
      m_owns_message = free_on_delete;

      // if we have the parsed version of the message, we don't need the raw version
      m_raw_data.clear();
    }

    int8_t get_type() const { return m_type; }
    const Message *message() const { return m_message; }
    std::string &buffer() { return m_raw_data; }

  private:
    std::string m_raw_data;
    int8_t m_type;
    Message *m_message;
    bool m_owns_message;
  };

  typedef Memory_new<Request>::Unique_ptr Request_unique_ptr;

} // namespace ngs

#endif // _NGS_MESSAGE_H_
