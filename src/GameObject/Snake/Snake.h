#pragma once
#include <list>

#include "GameManager/GameManager.h"
#include "GameObject/GameObject.h"

class Snake : public GameObject {
public:
    enum MOVE_TYPE_ {
        MOVE_TYPE_NORMAL   = 0,
        MOVE_TYPE_REVERSED = 1,
    };

    Snake(SDL_Renderer* renderer);
    ~Snake() override;

    void Render(SDL_Renderer* renderer) override;
    void Update(std::chrono::milliseconds delta_time) override;
    void HandleInput(SDL_Event& event) override;

    void         Create(const DIFFICULTY_ difficulty);
    void         IncrementBody();
    void         ReverseSnake();
    Vector2<int> GetHeadCoordinates();

private:
    std::chrono::milliseconds time_between_movements = std::chrono::milliseconds(150);
    std::chrono::milliseconds passed_time            = std::chrono::milliseconds(0);

    MOVE_TYPE_ move_type = MOVE_TYPE_NORMAL;

    Vector2<int>            head_coordinates;
    std::list<Vector2<int>> snake_body;
    Vector2<int>            prev_tail_coordinates;

    Vector2<int> direction;
    Vector2<int> new_direction;

    SDL_Texture* head_texture;
    SDL_Texture* body_texture;
};