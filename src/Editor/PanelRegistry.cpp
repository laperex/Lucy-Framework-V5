#include "PanelRegistry.h"

void lucy::PanelRegistry::Init() {
	Add<PanelInstance_Game>();
	Add<PanelInstance_Editor>();
	Add<PanelInstance_SceneHeirarchy>();
	Add<PanelInstance_Inspector>();
}

