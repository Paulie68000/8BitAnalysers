#pragma once

#include <cstdint>
#include "CodeAnalyser/CodeAnalyserTypes.h"
#include "CodeAnalyser/UI/MemoryAccessGrid.h"
#include "CodeAnalyser/UI/GraphicsViewer.h"
#include "Misc/EmuBase.h"

class FCodeAnalysisState;
class FGraphicsView;
class FC64Emulator;
class FC64GraphicsViewer;

enum class EC64ScreenMode
{
	HiresText,
	MulticolourText,
	HiresBitmap,
	MulticolourBitmap,
	ECMText,

	Invalid
};

enum class EGraphicsMemoryAccess
{
	Characters,
	Pixels,
	MulticolourAttributes,
	ColourRAM
};

class FC64ScreenAccessGrid : public FMemoryAccessGrid
{
public:
	FC64ScreenAccessGrid(FC64GraphicsViewer* pViewer);
	void OnDraw() override;
	FAddressRef GetGridSquareAddress(int x, int y) override;
private:
	FC64GraphicsViewer*	GraphicsViewer = nullptr;
};

class FC64GraphicsViewer : public FGraphicsViewer
{
friend class FC64ScreenAccessGrid;
public:
			FC64GraphicsViewer(FC64Emulator *pEmu);
	bool	Init() override;
	void	Shutdown() override;
	void	DrawUI() override;

	virtual const uint32_t* GetCurrentPalette() const override { return CurrentPalette; }

private:
	void	DrawCharacterBankCombo();
	void	DrawScreenBankCombo();
	void	DrawBitmapBankCombo();
	void	DrawMemoryAccessCombo();

	void	DrawSpritesViewer();
	void	DrawCharactersViewer();

	void	DrawCharacterScreen(bool bMulticolour, bool ECM);
	void	DrawBitmapScreen(bool bMulticolour);
	//FAddressRef GetAddressOfCharData(int x, int y);
	//void	DrawScreenAccessOverlay(float x,float y, bool bBitmapMode);

	void	DrawScreenViewer() override;
	void	DrawHiResSpriteAt(uint16_t addr, int xp, int yp);
	void	DrawMultiColourSpriteAt(uint16_t addr, int xp, int yp);
private:
	FC64Emulator*		C64Emu = nullptr;
	FCodeAnalysisState* CodeAnalysis = nullptr;

	FGraphicsView*		CharacterView = nullptr;
	FGraphicsView*		SpriteView = nullptr;
	FGraphicsView*		ScreenView = nullptr;
	
	int					VicBankNo = 0;
	int					ScreenBankNo = 0;
	int					BitmapBankNo = 0;
	int					CharacterBankNo = 0;
	EC64ScreenMode		ScreenMode = EC64ScreenMode::HiresText;

	bool			SpriteMultiColour = false;
	bool			CharacterMultiColour = false;
	uint32_t		SpriteCols[4];	// colours to draw sprites
	uint32_t		CharCols[4];	// colours to draw characters
	uint32_t		CurrentPalette[4];	// 'current palette'

	// For screen access view
	EGraphicsMemoryAccess	MemoryAccessDisplay = EGraphicsMemoryAccess::Characters;
	FC64ScreenAccessGrid*	ScreenAccessGrid = nullptr;

	FAddressRef	SelectedCharAddress;
	int			SelectedCharX = -1;
	int			SelectedCharY = -1;
};