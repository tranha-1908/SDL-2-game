Họ và tên: Trần Thị Nguyên Hà
Mã sinh viên: 24010116
Lớp môn học: INT2215_5

I.Giới thiệu game:

- Tên game : Sự phẫn nộ của bầy chim (Angry Bird)
- Video minh họa game: https://drive.google.com/file/d/1QeauWKdd0mM5xFTcMiQfYERVsQyhxDrl/view?usp=sharing
- Link GitHub: https://github.com/tranha-1908/SDL-2-game.git
1. Hướng dẫn:
* Màn hình chờ:
- Nhấn nút PLAY để vào chơi
* In game:
+ Góc phải:
	- Nhấn biểu tượng (x) để đóng trò chơi
	- Nhấn biểu tượng loa để bật, tắt âm
+ Góc trái: Thông tin số lượt bắn, số mục tiêu còn lại, điểm; 
+ Cách điều khiển:
	- Di chuyển chuột để điều chỉnh quỹ đạo bắn ( KÉO CHUỘT VỀ GÓC DƯỚI BÊN TRÁI CHIẾC NỎ)
		+ Càng ra xa lực bắn càng mạnh;
		+ Càng xuống thấp góc bắn càng cao;
	- Ấn chuột trái để bắn
* Kết thúc:
- Nhấn biểu tượng (G) để chơi lại
2. Luật chơi:
- Bạn có 20 lượt bắn chim nhằm tiêu diệt 8 con heo;
	+ Mỗi chú chim: 1 mạng, sát thương: 9 ô;
	+ Mỗi con heo: 2 mạng, điểm thưởng tiêu diệt: 5000;
-Tường, gỗ có 3 loại:
	+ Loại 1: có khung sắt, 	chống chịu: 3, điểm thưởng tiêu diệt: 500;
	+ Loại 2: không có khung sắt, 	chống chịu: 2, điểm thưởng tiêu diệt: 200;
	+ Loại 1: bẹo hình bẹo dạng, 	chống chịu: 1, điểm thưởng tiêu diệt: 100;
- Nếu tiêu diệt hết heo trong 20 lượt => bạn THẮNG
- Nếu hết chim trước => chơi lại

II.Thư viện, folder sử dụng:

- Xử lý đồ họa: SDL 2.0
- Xử lý âm thanh: SDL_mixer
- Xử lý phông chữ: SDL_ttf;
- Xử lý hình ảnh: SDL_image;
- Folder image: Chứa hình ảnh game: ảnh chờ, ảnh nền, ảnh thông báo, ảnh các nút chức năng, ảnh hiệu ứng nổ, ảnh chim...
- Folder map: chứa hình ảnh tường, heo
- Folder audio: Chứa hiệu ứng âm thanh, nhạc nền được sử dụng trong game


III.Cấu trúc của project game:

- main.cpp: Luồng điều khiển logic chính của game, chứa hàm khởi tạo, hàm điều khiển và vòng lặp game
	- Hàm khởi tạo tất cả;
	- Hàm Reset game;
	- Hàm vận hành màn hình chờ
	- Hàm xử lí kết thúc game
	- Hàm đóng chương trình
	- Hàm main gồm vòng lặp game;
- Common_function: 
	- Chứa các khai báo window, renderer, event, music..
	- Chứa các hằng số được định nghĩa cho game...
- Base_object : 
	- Gồm các hàm LoadImg, Render, đặt và lấy tọa độ
	- Hàm xử lí tín hiệu chuột khi ấn chọn các nút chức năng
	- Là cơ sở để phát triển các lớp khác
- Game_map:
	- tải 1 file dữ liệu số "map_.txt" biểu diễn tường và heo;
	- kế thừa từ base_object để vẽ map lên màn hình
- Main_object: kế thừa từ base_object
	- Quản lý điểm, lượng chim, lượng heo, xử lý kết quả game...
	- Hàm vẽ trước quỹ đạo bay
	- Hàm vẽ quỹ đạo chim bay
	- Hàm reset kết quả khi chơi lại
- Bird_object :	kế thừa từ base_object
	- Quản lý các biến về trạng thái di chuyển, tọa độ ban đầu, vận tốc, thời gian..;
	- Hàm tính toán quỹ đạo bay
	- Hàm kiểm tra va chạm;
	- Hàm hiệu ứng nổ, âm thanh nổ, tính điểm...

