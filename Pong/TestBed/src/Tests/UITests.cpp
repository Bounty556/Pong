#include "UITests.h"

#include <Memory/MemoryManager.h>
#include <UI/UI.h>
#include <UI/UIContainer.h>
#include <UI/UIPalette.h>
#include <UI/UIText.h>

#include "../TestMacros.h"

void BasicUIContainerTest()
{
	START_MEMORY_CHECK();

	Soul::UIContainer container(0.0f, 0.0f, 100.0f, 100.0f);

	ASSERT_EQUAL(container.GetSize(), sf::Vector2f(100.0f, 100.0f), "Failed to store container size.");

	ASSERT_EQUAL(container.GetAnchorPosition(Soul::UI::TopLeft), sf::Vector2f(0.0f, 0.0f), "Failed to get correct anchor position.");
	ASSERT_EQUAL(container.GetAnchorPosition(Soul::UI::TopMiddle), sf::Vector2f(50.0f, 0.0f), "Failed to get correct anchor position.");
	ASSERT_EQUAL(container.GetAnchorPosition(Soul::UI::TopRight), sf::Vector2f(100.0f, 0.0f), "Failed to get correct anchor position.");
	ASSERT_EQUAL(container.GetAnchorPosition(Soul::UI::MiddleLeft), sf::Vector2f(0.0f, 50.0f), "Failed to get correct anchor position.");
	ASSERT_EQUAL(container.GetAnchorPosition(Soul::UI::MiddleMiddle), sf::Vector2f(50.0f, 50.0f), "Failed to get correct anchor position.");
	ASSERT_EQUAL(container.GetAnchorPosition(Soul::UI::MiddleRight), sf::Vector2f(100.0f, 50.0f), "Failed to get correct anchor position.");
	ASSERT_EQUAL(container.GetAnchorPosition(Soul::UI::BottomLeft), sf::Vector2f(0.0f, 100.0f), "Failed to get correct anchor position.");
	ASSERT_EQUAL(container.GetAnchorPosition(Soul::UI::BottomMiddle), sf::Vector2f(50.0f, 100.0f), "Failed to get correct anchor position.");
	ASSERT_EQUAL(container.GetAnchorPosition(Soul::UI::BottomRight), sf::Vector2f(100.0f, 100.0f), "Failed to get correct anchor position.");

	ASSERT_EQUAL(container.GetUIPalette().GetColor(0), sf::Color::White, "Failed to get UIPalette color.");

	ASSERT_EQUAL(container.GetAnchorWeight(), 1.0f, "Incorrect anchor weight.");
	ASSERT_EQUAL(container.GetMainAnchor(), Soul::UI::None, "Incorrect anchor weight.");
	ASSERT_EQUAL(container.GetWeightingAnchor(), Soul::UI::MiddleMiddle, "Incorrect anchor weight.");

	END_MEMORY_CHECK();
}

void UIPaletteTest()
{
	START_MEMORY_CHECK();

	Soul::UIPalette palette(3, sf::Color::Blue, sf::Color::White, sf::Color::Black);

	ASSERT_EQUAL(palette.GetColor(0), sf::Color::Blue, "Failed to get UIPalette color.");
	ASSERT_EQUAL(palette.GetColor(1), sf::Color::White, "Failed to get UIPalette color.");
	ASSERT_EQUAL(palette.GetColor(2), sf::Color::Black, "Failed to get UIPalette color.");

	Soul::UIContainer container(0.0f, 0.0f, 0.0f, 0.0f);
	container.SetUIPalette(palette);

	ASSERT_EQUAL(container.GetUIPalette().GetColor(0), sf::Color::Blue, "Failed to store UIPalette in container.");
	ASSERT_EQUAL(container.GetUIPalette().GetColor(1), sf::Color::White, "Failed to store UIPalette in container.");
	ASSERT_EQUAL(container.GetUIPalette().GetColor(2), sf::Color::Black, "Failed to store UIPalette in container.");

	ASSERT_EQUAL(palette.GetColor(10), sf::Color::Black, "Failed to handle out of bounds color palette index.");

	END_MEMORY_CHECK();
}

void UITests::RunAllTests()
{
	RUN_TEST(BasicUIContainerTest);
	RUN_TEST(UIPaletteTest);
}