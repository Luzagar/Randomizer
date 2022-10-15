#include <cstdint>

#include "game_patch/game_patch.h"
#include "main.h"
#include "tp/d_a_shop_item_static.h"
#include "tp/d_item.h"
#include "tp/d_item_data.h"

namespace mod::game_patch
{
    void _02_modifyFoolishShopModel( uint16_t shopID )
    {
        using namespace libtp::tp::d_a_shop_item_static;

        // Set the shop model of the Foolish Item ID to the model of a random important item.
        libtp::tp::d_item_data::ItemResource* itemResourcePtr = &libtp::tp::d_item_data::item_resource[0];
        constexpr uint32_t modelListSize = TOTAL_FOOLISH_ITEM_MODELS;

        uint32_t randomIndex = ulRand( &randNext, modelListSize );
        uint32_t shopModelItemID = _04_verifyProgressiveItem( randomizer, foolishModelItemList[randomIndex] );

        shopItemData[shopID].arcName = itemResourcePtr[shopModelItemID].arcName;
        shopItemData[shopID].modelResIdx = itemResourcePtr[shopModelItemID].modelResIdx;
        shopItemData[shopID].wBckResIdx = itemResourcePtr[shopModelItemID].bckResIdx;
        shopItemData[shopID].wBrkResIdx = itemResourcePtr[shopModelItemID].brkResIdx;
        shopItemData[shopID].wBtpResIdx = itemResourcePtr[shopModelItemID].btpResIdx;
        shopItemData[shopID].tevFrm = itemResourcePtr[shopModelItemID].tevFrm;

        libtp::gc_wii::os_cache::DCFlushRange( reinterpret_cast<void*>( &shopItemData[shopID] ),
                                               sizeof( libtp::tp::d_a_shop_item_static::ShopItemData ) );
    }
}     // namespace mod::game_patch