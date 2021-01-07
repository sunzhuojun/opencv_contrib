// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.
//
// Tencent is pleased to support the open source community by making WeChat QRCode available.
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.

/*
 *  str.cpp
 *  zxing
 *
 *  Created by Christian Brunschen on 20/05/2008.
 *  Copyright 2008 ZXing authors All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "zxing/common/str.hpp"

#include <cstring>

using std::string;
using zxing::Ref;
using zxing::String;
using zxing::StrUtil;

using namespace std;

String::String(const std::string& text) : text_(text) {}

String::String(int capacity) { text_.reserve(capacity); }

const std::string& String::getText() const { return text_; }

char String::charAt(int i) const { return text_[i]; }

int String::size() const { return text_.size(); }

int String::length() const { return text_.size(); }

Ref<String> String::substring(int i) const { return Ref<String>(new String(text_.substr(i))); }

Ref<String> String::substring(int start, int end) const {
    return Ref<String>(new String(text_.substr(start, (end - start))));
}

void String::append(const std::string& tail) { text_.append(tail); }

void String::append(char c) { text_.append(1, c); }

void String::append(int d) {
    string str = StrUtil::numberToString(d);
    text_.append(str);
}

void String::append(Ref<String> str) { append(str->getText()); }

std::ostream& zxing::operator<<(std::ostream& out, String const& s) {
    out << s.text_;
    return out;
}

string StrUtil::COMBINE_STRING(string str1, string str2) {
    string str = str1;
    str += str2;
    return str;
}

string StrUtil::COMBINE_STRING(string str1, char c) {
    string str = str1;
    str += c;
    return str;
}

string StrUtil::COMBINE_STRING(string str1, int d) {
    string str = str1;
    str += numberToString(d);
    return str;
}

Ref<String> StrUtil::COMBINE_STRING(char c1, Ref<String> content, char c2) {
    Ref<String> str(new String(0));
    str->append(c1);
    str->append(content);
    str->append(c2);

    return str;
}

template <typename T>
string StrUtil::numberToString(T Number) {
    ostringstream ss;
    ss << Number;
    return ss.str();
}

template <typename T>
T StrUtil::stringToNumber(const string& Text) {
    istringstream ss(Text);
    T result;
    return ss >> result ? result : 0;
}

int StrUtil::indexOf(const char* str, char c) {
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == c) {
            return i;
        }
    }

    return -1;
}