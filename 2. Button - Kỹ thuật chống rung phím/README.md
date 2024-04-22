
# Buổi 2: Button - Xử lí lọc nhiễu ko dùng Delay

### 1. Khối Input Driver
![](https://i.imgur.com/P97DG2Z.png)      
Nhìn vào trong đường đi ta thấy 2 trở treo: Pull-up, Pull-down. Vậy mục đích của nó làm gì?   
-> Khi chưa biết mức Logic đầu vào (Floating) thì nó sẽ xác định mức Logic ban đầu.

### 2. Điện trở treo    
![](https://i.imgur.com/ZzTFx4O.png)        
Ở hình trên, nếu ko có điện trở treo thì chân GPIO sẽ ko biết được đầu vào nó đang ở mức Logic nào do nút chưa nhấn. 
- Pull-up: mức logic ban đầu là 1 khi nhấn nút xuống thì mức logic vào chân GPIO là 0.    
- Pull-down: mức logic ban đầu là 0 khi nhấn nút xuống thù mức logic vào chân GPIO là 1.          

#### * Lưu ý: STM32 đã tích hợp sẵn 2 chế độ ở trong nên chỉ cần cấu hình và dùng, ko cần mắc ở ngoài.          

### 3. Hàm đọc trạng thái của 1 chân
HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);      
x: Port nào?        
Pin: Chân số mấy?       
-> Hàm sẽ trả về: GPIO_PIN_RESET: nếu chân ở mức 0, GPIO_PIN_SET: nếu chân ở mức 1.     
### 4. Hiện tượng dội nút nhấn    
- Dội hay nhiễu hay rung nút nhấn là hiện tượng xảy ra khi ta nhấn/thả nút, khi đó, các bộ phận cơ làm bằng kim loại có khả năng đàn hồi của nút sẽ xuất hiện tiếp điểm để truyền tín hiệu đi qua tiếp điểm đó, nhưng vì tính đàn hồi nên các thành phần này sẽ không cố định ngay khi được bấm mà sẽ bị nảy tạo các tiếp điểm ngắt.
![](https://i.imgur.com/dJ2ZjhK.png)
![](https://i.imgur.com/AO3kw24.png)
Ở đây ta thấy, khi chỉ nhấn nút xuống rồi thả ra thì nó đã vào vòng if tận 4 lần.     
![](https://i.imgur.com/ky5Eoej.png)

### 5. Kỹ thuật xử lý rung phím của nút nhấn    
- Mô phỏng quá trình xử lý
![](https://i.imgur.com/Reb39xa.png)

### * Các sự kiện của nút nhấn:
- Nhấn nút: btn_pressing_callback;
- Nhả nút: btn_realese_callback;
- Nhấn giữ: btn_pressed_timeout_callback; -> Nhấn giữ lâu hơn 3s rồi thả
- Nhấn nhả: btn_pressed_short_callback; -> Nhấn phát nhả ra ngay, thời gian thực hiện bé hơn 1s
---> Code xử lý rung phím và các sự kiện nút nhấn ở trong file Button.

------------------------------------------------------------------
## BÀI TẬP         
1. Nhấn nút trên chân PA0 thì đèn trên chân PC13 bật, nhấn lần nữa đèn tắt.
2. 1 nút nhấn điều khiển 3 bóng đèn, nhấn lần 1 đèn 1 sáng, nhấn lần 2 thì đèn 2 sáng, nhấn lần 3 thì đèn 3 sáng, nhấn lần 4 thì 3 đèn nhấp nháy với tần số 5Hz, nhấn lần 5 thì 3 đèn tắt.          
-- Nút nhấn nối với PA0, 3 đèn lần lượt nối với PB3 PB4 PB5.            
-- Gợi ý: Sử dụng Kỹ thuật State Machine.        
- Yêu cầu: Ko sử dụng Delay và While           
     
