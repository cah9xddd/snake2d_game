#pragma once
#include "GameObject/GameObject.h"
#include "Game_Manager/Game_Manager.h"
#include "SDL2/SDL_image.h"
#include <list>
class Snake : public GameObject {
public:
    enum MOVE_TYPE_ {
        MOVE_TYPE_NORMAL = 0,
        MOVE_TYPE_REVERSED = 1,
    };
    Snake(SDL_Window* window);
    ~Snake();

    void Render(SDL_Renderer* renderer) override;
    void Update(double delta_time) override;
    void HandleInput(SDL_Event& event) override;

    void Create(const DIFFICULTY_ difficulty);
    void IncrementBody();
    void ReverseSnake();
private:
    float time_between_movements = 0.15f;
    float passed_time = 0;

    MOVE_TYPE_ move_type = MOVE_TYPE_NORMAL;

    std::list<Vector2<int>> snake_body;
    Vector2<int> prev_tail_coords;

    Vector2<int> direction;
    Vector2<int> new_direction;

    SDL_Texture* head_t;
    SDL_Texture* body_t;
};