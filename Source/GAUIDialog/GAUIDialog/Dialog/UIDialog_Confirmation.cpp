// Copyright (C) 2024 owoDra

#include "UIDialog_Confirmation.h"

#include "Foundation/ButtonWidget.h"
#include "GUIExtLogs.h"

#include "InputCoreTypes.h"
#include "CommonBorder.h"
#include "CommonRichTextBlock.h"
#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Components/SlateWrapperTypes.h"
#include "ICommonInputModule.h"
#include "CommonInputSettings.h"
#include "Input/Reply.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(UIDialog_Confirmation)


void UUIDialog_Confirmation::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Border_TapToCloseZone->OnMouseButtonDownEvent.BindDynamic(this, &ThisClass::HandleTapToCloseZoneMouseButtonDown);
}


void UUIDialog_Confirmation::SetupDialog(UUIDialogDescriptor* Descriptor, FDialogMessageResultDelegate ResultCallback)
{
	Text_Title->SetText(Descriptor->Header);
	RichText_Description->SetText(Descriptor->Body);

	EntryBox_Buttons->Reset<UButtonWidget>(
		[](UButtonWidget& Button)
		{
			Button.OnClicked().Clear();
		}
	);

	for (const auto& Action : Descriptor->ButtonActions)
	{
		if (ICommonInputModule::GetSettings().IsEnhancedInputSupportEnabled())
		{
			UInputAction* InputAction{ nullptr };

			switch (Action.Result)
			{
			case EDialogMessageResult::Confirmed:
				InputAction = ICommonInputModule::GetSettings().GetEnhancedInputClickAction();
				break;

			case EDialogMessageResult::Declined:
				InputAction = ICommonInputModule::GetSettings().GetEnhancedInputBackAction();
				break;

			case EDialogMessageResult::Cancelled:
				InputAction = CancelInputAction.IsValid() ? CancelInputAction.Get() : CancelInputAction.LoadSynchronous();
				break;

			default:
				UE_LOG(LogGameExt_UI, Warning, TEXT("Invalid DialogMessageResult type has set"));
				continue;
			}

			auto* Button{ EntryBox_Buttons->CreateEntry<UButtonWidget>() };
			Button->SetTriggeringEnhancedInputAction(InputAction);
			Button->OnClicked().AddUObject(this, &ThisClass::CloseConfirmationWindow, Action.Result);
			Button->SetButtonText(Action.OptionalDisplayText);
		}
		else
		{
			FDataTableRowHandle ActionRow;

			switch (Action.Result)
			{
			case EDialogMessageResult::Confirmed:
				ActionRow = ICommonInputModule::GetSettings().GetDefaultClickAction();
				break;

			case EDialogMessageResult::Declined:
				ActionRow = ICommonInputModule::GetSettings().GetDefaultBackAction();
				break;

			case EDialogMessageResult::Cancelled:
				ActionRow = CancelAction;
				break;

			default:
				UE_LOG(LogGameExt_UI, Warning, TEXT("Invalid DialogMessageResult type has set"));
				continue;
			}

			auto* Button{ EntryBox_Buttons->CreateEntry<UButtonWidget>() };
			Button->SetTriggeringInputAction(ActionRow);
			Button->OnClicked().AddUObject(this, &ThisClass::CloseConfirmationWindow, Action.Result);
			Button->SetButtonText(Action.OptionalDisplayText);
		}
	}

	OnResultCallback = ResultCallback;
}

void UUIDialog_Confirmation::KillDialog()
{
}


void UUIDialog_Confirmation::CloseConfirmationWindow(EDialogMessageResult Result)
{
	DeactivateWidget();
	OnResultCallback.ExecuteIfBound(Result);
}


FEventReply UUIDialog_Confirmation::HandleTapToCloseZoneMouseButtonDown(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = FReply::Unhandled();

	if (MouseEvent.IsTouchEvent() || MouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		CloseConfirmationWindow(EDialogMessageResult::Declined);
		Reply.NativeReply = FReply::Handled();
	}

	return Reply;
}
