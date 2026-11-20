#pragma once
/*
* +-------------------------------------+
* File   : [worldMap.h]
* Author : 小原崚介
* Date   : 2026/11/20
*
*
* マスターデータに基づいたステージの作成
* 当たり判定、ステージをまとめて管理
*
* +-------------------------------------+
*/
#include "stage.h"

void InitializeWorldMap();
void FinalizeWorldMap(void);
void UpdateWorldMap(void);
void DrawWorldMap(void);

const STAGE_ID GetSelectStageId();