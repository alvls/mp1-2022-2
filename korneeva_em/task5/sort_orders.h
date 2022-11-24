#pragma once

const char sort_orders[][16] = {
	"По возрастанию",
	"По убыванию"
};

#define AVAILABLE_SORT_ORDERS (int)(sizeof(sort_orders) / sizeof(sort_orders[0]))