// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "420";
    const CScript genesisOutputScript = CScript() << ParseHex("040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 3000000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // one day
        consensus.nPowTargetSpacing = 42;
        consensus.nPowTargetSpacing2 = 90; // 1.5 min block spacing
        consensus.checkpointPubKey = "045864a97ae62be8df3a0479e17671696e0d8132bfd2391e638f7dcf89bc33aa5f0eef639fc121c585a5af949dac261a18aa8688ce07300d4e467f8f213ea0a529";
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 21600; // 75% of 28800
        consensus.nMinerConfirmationWindow = 28800;
        consensus.nForkOne = 2282000;
        consensus.nForkTwo = 3030000;
        consensus.nForkThree = 7175000;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1533081600; // Wednesday, 1 August 2018 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1564617600; // Thursday, 1 August 2019 00:00:00

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1533081600; // Wednesday, 1 August 2018 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1564617600; // Thursday, 1 August 2019 00:00:00

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xb9;
        pchMessageStart[3] = 0xde;
        nDefaultPort = 39348;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1400408750, 325433, 0x1e0ffff0, 1, 420 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000a10f7ce671e773330376ce892a6c0b93fbc05553ebbf659b11e3bf9188d"));
        assert(genesis.hashMerkleRoot == uint256S("0x2a4b0da444f96adf29d6bccf65fa6d558ccbbc4b0fc5c5b3088fc03d5c364558"));

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.push_back(CDNSSeedData("193.149.129.63", "193.149.129.63", false));
        vSeeds.push_back(CDNSSeedData("193.149.190.225", "193.149.190.225", false));
        vSeeds.push_back(CDNSSeedData("95.214.234.215", "95.214.234.215", false));
        vSeeds.push_back(CDNSSeedData("95.214.234.216", "95.214.234.216", false));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,156);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 5500000, uint256S("0x000000000008500709c9df74e3b0d3267e6b1c2919fa6be75226e925712bc3be"))
            ( 6000000, uint256S("0x000000000008aee62db6e93080308f828adb1f6c3be8592a789deed5b5708b4f"))
            ( 6600000, uint256S("0x00000000000376992ade79530ec32a240918502e3c79b6b2b0842d04de8bfc20"))
            ( 7000000, uint256S("0x000000000157f36da81fa922e14d02c49c0e8894e65c50589a9a006e1e48d917"))
            ( 7100000, uint256S("0x000005e775a9e21d833d08f766db79905705a91eab05c8718b945e4eee75761c"))
            ( 7150000, uint256S("0x0000001d4105a13df91c6d2c6a83e355fdb23a2c5c132e26b14bcf090507a610"))
            ( 7160000, uint256S("0x000000368d1652ec4594feaf13d7b10ecfa3832409d480aa23d2e0a405a9cfaa"))
            ( 7161500, uint256S("0x00000bdc75aea2a17199f2586d19eef85e16c176b722624681b28a72c38b372c")),
            1728730733, // * UNIX timestamp of last checkpoint block
            8246282,   // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            3100.0     // * estimated number of transactions per day after checkpoint
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 3000000;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // one day
        consensus.nPowTargetSpacing = 42;
        consensus.checkpointPubKey = "048dc3106fba17f0bcefb289f14a8e248e210ae6f96cc2e512b84ba88f9bc08669078a9e4d0144d6573d035a62d84224f380427d2cbdb763da56aeac6cf50b13e3";
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 2160;
        consensus.nMinerConfirmationWindow = 2880;
        consensus.nForkOne = 1500;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1533081600; // Wednesday, 1 August 2018 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1564617600; // Thursday, 1 August 2019 00:00:00

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1533081600; // Wednesday, 1 August 2018 00:00:00
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1564617600; // Thursday, 1 August 2019 00:00:00

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");

        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0xde;
        nDefaultPort = 29347;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1400408750, 325433, 0x1e0ffff0, 1, 420 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000a10f7ce671e773330376ce892a6c0b93fbc05553ebbf659b11e3bf9188d"));
        assert(genesis.hashMerkleRoot == uint256S("0x2a4b0da444f96adf29d6bccf65fa6d558ccbbc4b0fc5c5b3088fc03d5c364558"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("cannabiscoin.net", "testnet-seed.cannabiscoin.net", false));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            ( 0, uint256S("00000a10f7ce671e773330376ce892a6c0b93fbc05553ebbf659b11e3bf9188d")),
            1400408750,
            1,
            2778
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // one day
        consensus.nPowTargetSpacing = 42;
        consensus.checkpointPubKey = "048dc3106fba17f0bcefb289f14a8e248e210ae6f96cc2e512b84ba88f9bc08669078a9e4d0144d6573d035a62d84224f380427d2cbdb763da56aeac6cf50b13e3";
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.nForkOne = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 29347;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1400408750, 1, 0x207fffff, 1, 420 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x35e0eaea93bb51238d310f089a639d92402491b7e27365bb4fb08353ce1e4721"));
        assert(genesis.hashMerkleRoot == uint256S("0x2a4b0da444f96adf29d6bccf65fa6d558ccbbc4b0fc5c5b3088fc03d5c364558"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("35e0eaea93bb51238d310f089a639d92402491b7e27365bb4fb08353ce1e4721")),
            0,
            0,
            0
        };
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
 
