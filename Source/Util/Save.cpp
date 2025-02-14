#include "StdAfx.h"
#include "EditArchive.h"
#include "Save.h"

class TriggerInterfaceImpl : public TriggerInterface
{
public:
	const char* actionComboList() {
		return EditClassDescriptor<Action>::comboListAlt().c_str();
	}

	const char* conditionComboList() {  
		return EditClassDescriptor<Condition>::comboListAlt().c_str();
	}

	ActionPtr createAction(int typeIndex) {
		ActionPtr action;
		EditIArchive(EditClassDescriptor<Action>::treeNodeFunc(typeIndex)) >> WRAP_NAME(action, 0);
		return action;
	}

	ConditionPtr createCondition(int typeIndex) {
		ConditionPtr condition;
		EditIArchive(EditClassDescriptor<Condition>::treeNodeFunc(typeIndex)) >> WRAP_NAME(condition, 0);
		return condition;
	}

	const char* actionName(const Action& action) {
		return EditClassDescriptor<Action>::instance().nameAlt(action);
	}

	const char* conditionName(const Condition& condition) {
		return EditClassDescriptor<Condition>::instance().nameAlt(condition);
	}

	bool editCondition(Trigger& trigger, HWND hwnd) {
		if(!trigger.condition)
			return false;
		EditArchive editArchive(hwnd, TreeControlSetup(0,0,500,400,"editConditionSetup",true));
		return editArchive.edit(trigger.condition);
	}

	bool editTrigger(Trigger& trigger, HWND hwnd) {
		EditArchive editArchive(hwnd, TreeControlSetup(0,0,500,400,"editConditionSetup",true));
		return editArchive.edit(trigger);
	}

	void* malloc(size_t n) {
		return ::malloc(n);
	}

	void free(void* p) {
		::free(p);
	}
};

TriggerInterface& triggerInterface() {
    TriggerInterface& ti = Singleton<TriggerInterfaceImpl>::instance();
	return ti;
}
