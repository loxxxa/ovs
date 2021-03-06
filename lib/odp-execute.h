/*
 * Copyright (c) 2013 Nicira, Inc.
 * Copyright (c) 2013 Simon Horman
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef EXECUTE_ACTIONS_H
#define EXECUTE_ACTIONS_H 1

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "openvswitch/types.h"

struct nlattr;
struct dpif_packet;
struct pkt_metadata;

/* Remaining packets are dropped if the callback returns a value < 'cnt'. */
typedef int (*odp_execute_cb)(void *dp, struct dpif_packet **packets, int cnt,
                              struct pkt_metadata *,
                              const struct nlattr *action, bool may_steal);

/* Actions that need to be executed in the context of a datapath are handed
 * to 'dp_execute_action', if non-NULL.
 * The caller relinquishes ownership of the 'packets' if 'steal' is 'true'.
 * In this case the packet pointers in 'packets' will be set to NULL to
 * enforce the ownership transfer. */
void odp_execute_actions(void *dp, struct dpif_packet **packets, int cnt,
                         bool steal, struct pkt_metadata *,
                         const struct nlattr *actions, size_t actions_len,
                         odp_execute_cb dp_execute_action);
#endif
