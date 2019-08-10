#include "Animation.h"

void Animation::AddFrame(Sprite *sprite, DWORD time)
{
	DWORD t = time;
	//Nếu không có giá trị time (hay = 0) thì thiết lập thời gian mặc định defaultTime
	if (time == 0) t = this->defaultDelayTime;
	//Lấy frame
	pair <Sprite *, DWORD> frame(sprite, t);
	//Thêm frame mới vào vector frames
	frames.push_back(frame);
	curFrame = -1;
	done = false;
}
void Animation::Render(SpriteData spriteData)
{
	//Lấy giá trị thời gian hiện tại
	DWORD now = GetTickCount();
	//Nếu currentFrame = -1 thì khởi tạo giá trị cho các biến
	if (this->curFrame == -1)
	{
		curFrame = 0;
		lastFrameTime = now;
		done = false;
	}

	frames[curFrame].first->SetData(spriteData);
	//Vẽ frame hiện tại
	Graphics::GetInstance()->Draw(frames[curFrame].first);

	//Xử lí các frames

	//Lấy thời gian tồn tại của frame hiện tại
	DWORD t = frames[curFrame].second;
	//Nếu thời gian giữa hiện tại và frame hiện tại lớn hơn thời gian tồn tại của frame đó thì
	if (now - lastFrameTime > t)
	{
		//Tăng lên frame tiếp theo
		curFrame++;
		//Thời gian frame mới sẽ đặt bằng thời gian hiện tại
		lastFrameTime = now;
		//Nếu là frame cuối thì quay lại frame đầu
		if (curFrame == frames.size())
		{
			curFrame = -1;
			done = true;
		}
		else
			done = false;
		//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
	}
}