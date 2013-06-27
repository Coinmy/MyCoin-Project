// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 MyCoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (1,      uint256("0x19d76d5025853bb025faeaba00c38e5c1c055856b48de039eaccce364c79236a"))
            (2,      uint256("0xdc099a413e792416b89f4e134f02e9ee466c3e756b3e5f69ec29dd826a1e82c1"))
            (50,     uint256("0xbde3ecf3a8bae865bcdfe71a59f61d830ac4afef6f8c42cb738e544e153dd004"))
            (500,    uint256("0x899cb0fdc8926d36e9544c2c4d89214062d7ba8e5cc5296e1b9be5e9c707398a"))
            (1000,   uint256("0x1e149751aebf71b8493ca147103cd1e11cb3d7085fb6e121d8c8f2dbaf6d6d00"))
            (2333,   uint256("0x572a50f06f2680e16852554ab2d6155385439dbdaa7c2229006e6283769f4fd7"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
		
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
