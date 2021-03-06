/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "api/s2n.h"
#include "stuffer/s2n_stuffer.h"
#include "utils/s2n_mem.h"

#include <assert.h>
#include <string.h>

#include <cbmc_proof/cbmc_utils.h>
#include <cbmc_proof/proof_allocators.h>
#include <cbmc_proof/make_common_datastructures.h>

void s2n_stuffer_certificate_from_pem_harness() {
    /* Non-deterministic inputs. */
    struct s2n_stuffer *pem = cbmc_allocate_s2n_stuffer();
    __CPROVER_assume(s2n_stuffer_is_valid(pem));
    __CPROVER_assume(s2n_stuffer_is_bounded(pem, MAX_BLOB_SIZE));

    struct s2n_stuffer *asn1 = cbmc_allocate_s2n_stuffer();
    __CPROVER_assume(s2n_stuffer_is_valid(asn1));

    /* Non-deterministically set initialized (in s2n_mem) to true. */
    if(nondet_bool()) {
        s2n_mem_init();
    }

    /* Operation under verification. */
    s2n_stuffer_certificate_from_pem(pem, asn1);

    /* Post-conditions. */
    assert(s2n_stuffer_is_valid(pem));
    assert(s2n_stuffer_is_valid(asn1));
}
