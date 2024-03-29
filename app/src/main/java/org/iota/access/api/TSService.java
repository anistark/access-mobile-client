/*
 *  This file is part of the IOTA Access distribution
 *  (https://github.com/iotaledger/access)
 *
 *  Copyright (c) 2020 IOTA Stiftung.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

package org.iota.access.api;

import org.iota.access.api.model.token_server.TSEmptyResponse;
import org.iota.access.api.model.token_server.TSFundRequest;
import org.iota.access.api.model.token_server.TSSendRequest;
import org.iota.access.api.model.token_server.TSBalanceRequest;
import org.iota.access.api.model.token_server.TSBalanceResponse;
import org.iota.access.api.model.token_server.TSDataResponse;

import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.PUT;

/**
 * Interface for communication with Token Server
 */
public interface TSService {
    @PUT("/balance")
    Call<TSDataResponse<TSBalanceResponse>> getBalance(@Body TSBalanceRequest request);

    @PUT("/fund")
    Call<TSEmptyResponse> fundAccount(@Body TSFundRequest request);

    @PUT("/send")
    Call<TSEmptyResponse> sendTokens(@Body TSSendRequest request);
}
