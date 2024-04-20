// No copyright


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	//when we set the widget controller, we also make sure to call the blueprint set function
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
