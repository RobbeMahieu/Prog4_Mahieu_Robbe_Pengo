#include "MoveCommand.h"
#include "GameTime.h"

using namespace pengo;

MoveCommand::MoveCommand(engine::GameObject* object, glm::vec2 direction, float speed)
	: Command()
	, m_pObject{ object }
	, m_Direction{ direction }
	, m_Speed{ speed }
{

}

void MoveCommand::Execute() {
	float elapsedSec{ engine::GameTime::GetInstance().GetElapsedSec() };

	glm::vec3 pos = m_pObject->GetLocalPosition();
	pos.x += m_Speed * elapsedSec * m_Direction.x;
	pos.y += m_Speed * elapsedSec * m_Direction.y;
	m_pObject->SetLocalPosition(pos);
}