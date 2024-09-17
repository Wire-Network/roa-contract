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
        ACTION addpolicy(const name& username, const name& contract_name, const type& cpu, const type& net, const type& ram, const type& timelock);

        /**
         * @brief Remove a contract from a T1 Node Owner's whitelist.
         * 
         * @param username The T1 Node Owner's username.
         * @param contract_name The contract's username.
         * @return ACTION 
         */
        ACTION delpolicy(const name& username, const name& contract_name);
        
        

    private:

        /**
         * @brief A table scoped by T1 Node Owners account name. Tracks the name of the contract and its alloted resource limits.
         */
        TABLE policies {
            uint64_t policyId;          // Primary key: Unique identifier for the policy
            sysio::name contractName;   // Username of the contract whitelisted
            sysio::asset cpu;           // Allotment of CPU ( % of T1 holders resources )
            sysio::asset net;           // Allotment of NET ( % of T1 holders resources )
            uint64_t ram;               // Allotment of RAM ( % of T1 holders resources )
            sysio::name t1owner;        // T1 Node Owner's username
            uint64_t timeblock;         // Block number when the policy expires

            uint64_t primary_key() const { return policyId; }
            uint64_t by_name() const { return username.value; }
        }

        typedef multi_index<"policies"_n, policies,
            indexed_by<"byname"_n, const_mem_fun<policies, uint64_t, &policies::by_name>>
        > policies_t;

        TABLE userres {
            sysio::name username;         // Username of the T1 Node Owner
            sysio::asset cpu;      // Total CPU allocated to the user
            sysio::asset net;      // Total NET allocated to the user
            uint64_t ram;          // Total RAM allocated to the user

            uint64_t primary_key() const { return username.value; }
        };

        typedef multi_index<"userres"_n, userres> userres_t;
}