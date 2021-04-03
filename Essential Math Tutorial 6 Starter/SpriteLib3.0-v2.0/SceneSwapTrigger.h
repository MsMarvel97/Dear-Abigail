#pragma once
#include "Trigger.h"
class SceneSwapTrigger :
    public Trigger
{
   void OnEnter() override;
   void OnExit() override;
};

