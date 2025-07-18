// Copyright (C) 2019-2020 Zilliz. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied. See the License for the specific language governing permissions and limitations under the License
#include "segcore/token_stream_c.h"
#include "token-stream.h"
#include "monitor/scope_metric.h"

void
free_token_stream(CTokenStream token_stream) {
    SCOPE_CGO_CALL_METRIC();

    delete static_cast<milvus::tantivy::TokenStream*>(token_stream);
}

bool
token_stream_advance(CTokenStream token_stream) {
    SCOPE_CGO_CALL_METRIC();

    return static_cast<milvus::tantivy::TokenStream*>(token_stream)->advance();
}

// Note: returned token must be freed by the caller using `free_token`.
const char*
token_stream_get_token(CTokenStream token_stream) {
    SCOPE_CGO_CALL_METRIC();

    return static_cast<milvus::tantivy::TokenStream*>(token_stream)
        ->get_token_no_copy();
}

CToken
token_stream_get_detailed_token(CTokenStream token_stream) {
    SCOPE_CGO_CALL_METRIC();

    auto token = static_cast<milvus::tantivy::TokenStream*>(token_stream)
                     ->get_detailed_token();
    return CToken{token.token,
                  token.start_offset,
                  token.end_offset,
                  token.position,
                  token.position_length};
}

void
free_token(void* token) {
    SCOPE_CGO_CALL_METRIC();

    free_rust_string(static_cast<const char*>(token));
}
