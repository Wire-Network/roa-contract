#pragma once

#include <sysio/sysio.hpp>
#include <sysio/print.hpp>

using namespace sysio;

CONTRACT roa : public contract {
    public:
        /**
         * @brief Add a contract to a T1 Node Owner's whitelist.
         * 
         * @param username The T1 Node Owner's username.
         * @param contract_name The contract's username.
         * @param cpu The amount of CPU allocated to the contract from T1 Node Owner's pool.
         * @param net The amount of NET allocated to the contract from T1 Node Owner's pool.
         * @param ram The amount of RAM allocated to the contract from T1 Node Owner's pool.
         * @param timelock A timestamp for when the policy expires ( Expires == When the T1 node owner is allowed to delete the policy and free up their allocation )
         * @return ACTION 
         */
        ACTION whitelistadd(const name& username, const name& contract_name, const type& cpu, const type& net, const type& ram, const type& timelock);

        /**
         * @brief Remove a contract from a T1 Node Owner's whitelist.
         * 
         * @param username The T1 Node Owner's username.
         * @param contract_name The contract's username.
         * @return ACTION 
         */
        ACTION whitelistdel(const name& username, const name& contract_name);
        ACTION updateowners();

    private:

        /**
         * @brief A table scoped by T1 Node Owners account name. Tracks the name of the contract and its alloted resource limits.
         */
        TABLE policies_s {
            uint64_t key;               // Auto incrementing key
            sysio::name username;       // Username of the contract whitelisted
            type cpu;                   // Allotment of CPU ( % of T1 holders resources )
            type net;                   // Allotment of NET ( % of T1 holders resources )
            type ram;                   // Allotment of RAM ( % of T1 holders resources )

            uint64_t primary_key() const { return key; }
            uint64_t by_name() const { return username.value; }
        }

        typedef multi_index<"policies"_n, policies_s,
            indexed_by<"byname"_n, const_mem_fun<policies_s, uint64_t, &policies_s::by_name>>
        > policies_t;
}