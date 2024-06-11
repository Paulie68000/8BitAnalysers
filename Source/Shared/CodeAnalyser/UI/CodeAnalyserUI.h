#pragma once
#include <cstdint>

#include "../CodeAnalyserTypes.h"

struct FCodeAnalysisItem;
class FCodeAnalysisState;
struct FCodeAnalysisViewState;
struct FDataInfo;
struct FItem;
class FGraphicsView;

enum class ENumberDisplayMode;
enum class EDataItemDisplayType;
enum class EOperandType;


class FMemoryRegionDescGenerator
{
public:
	bool	InRegion(FAddressRef addr) const
	{
		return (addr.BankId == RegionBankId || RegionBankId == -1) && addr.Address >= RegionMin && addr.Address <= RegionMax;
	}
    void SetRegionBankId(int16_t bankId) { RegionBankId = bankId; }

	virtual const char* GenerateAddressString(FAddressRef addr) = 0;

	virtual void FrameTick() {}
    
protected:
	int16_t		RegionBankId = -1;	// -1 means any bank (needed for regions that span banks)
	uint16_t	RegionMin = 0xffff;
	uint16_t	RegionMax = 0;
};

const uint32_t kAddressLabelFlag_NoBank		= 0x0001;
const uint32_t kAddressLabelFlag_NoBrackets	= 0x0002;
const uint32_t kAddressLabelFlag_White		= 0x0004;

// UI
void ResetRegionDescs(void);
bool AddMemoryRegionDescGenerator(FMemoryRegionDescGenerator* pGen);
void UpdateRegionDescs(void);

void ShowCodeAccessorActivity(FCodeAnalysisState& state, const FAddressRef accessorCodeAddr);
void DrawCodeAddress(FCodeAnalysisState& state, FCodeAnalysisViewState& viewState, FAddressRef addr, uint32_t displayFlags = 0);
bool DrawAddressLabel(FCodeAnalysisState& state, FCodeAnalysisViewState& viewState, uint16_t addr, uint32_t displayFlags = 0);
bool DrawAddressLabel(FCodeAnalysisState& state, FCodeAnalysisViewState& viewState, FAddressRef addr, uint32_t displayFlags = 0);
int GetItemIndexForAddress(const FCodeAnalysisState& state, FAddressRef addr);
void DrawCodeAnalysisItem(FCodeAnalysisState& state, FCodeAnalysisViewState& viewState, const FCodeAnalysisItem& item);
bool DrawNumberTypeCombo(const char* pLabel, ENumberDisplayMode& numberMode);
bool DrawOperandTypeCombo(const char* pLabel, FCodeInfo* pCodeInfo);
bool DrawDataTypeCombo(const char* pLabel, EDataType& dataType);
bool DrawDataDisplayTypeCombo(const char* pLabel, EDataItemDisplayType& displayType, const FCodeAnalysisState& state);
bool DrawBitmapFormatCombo(EBitmapFormat& bitmapFormat, const FCodeAnalysisState& state);
bool DrawPaletteCombo(const char* pLabel, const char* pFirstItemLabel, int& paletteEntryIndex, int numColours=-1);
void DrawPalette(const uint32_t* palette, int numColours, float height = 0.f);
EDataItemDisplayType GetDisplayTypeForBitmapFormat(EBitmapFormat bitmapFormat);

void DrawSnippetToolTip(FCodeAnalysisState& state, FCodeAnalysisViewState& viewState, const FAddressRef addr);

void DrawCodeAnalysisData(FCodeAnalysisState &state, int windowId);
void DrawGlobals(FCodeAnalysisState& state, FCodeAnalysisViewState& viewState);

float DrawDataBinary(FCodeAnalysisState& state, const FDataInfo* pDataInfo);
void DrawDataInfo(FCodeAnalysisState& state, FCodeAnalysisViewState& viewState, const FCodeAnalysisItem &item, bool bDrawLabel = false, bool bEdit = true);
void DrawDataDetails(FCodeAnalysisState &state, FCodeAnalysisViewState& viewState, const FCodeAnalysisItem& item);
void ShowDataItemActivity(FCodeAnalysisState& state, FAddressRef addr);

void DrawComment(FCodeAnalysisState& state, FCodeAnalysisViewState& viewState, const FItem* pItem, float offset = 0.0f);

// util functions - move?
bool DrawU8Input(const char* label, uint8_t* value);
bool DrawAddressInput(FCodeAnalysisState& state, const char* label, FAddressRef& address);
bool DrawAddressInput(const char* label, uint16_t* value);
const char* GetBankText(const FCodeAnalysisState& state, int16_t bankId);
bool DrawBankInput(const FCodeAnalysisState& state, const char* label, int16_t& bankId, bool bAllowNone = false);
EBitmapFormat GetBitmapFormatForDisplayType(EDataItemDisplayType displayType);
int GetBppForBitmapFormat(EBitmapFormat bitmapFormat);
int GetNumColoursForBitmapFormat(EBitmapFormat bitmapFormat);
bool BitmapFormatHasPalette(EBitmapFormat bitmapFormat);
bool IsBitmapFormatDoubleWidth(EBitmapFormat bitmapFormat);

// config - move?
void DrawCodeAnalysisConfigWindow(FCodeAnalysisState& state);

namespace Markup
{ 
void SetCodeInfo(const FCodeInfo* pCodeInfo);
bool DrawText(FCodeAnalysisState& state, FCodeAnalysisViewState& viewState, const char* pText);
std::string ExpandString(const char* pText);
}


