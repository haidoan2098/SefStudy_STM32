
# Buổi 1: Tìm hiểu về STM32 BluePill & GPIO Blink LED

### 1. Giới thiệu về STM32F103C8T6
- Nguồn cung cấp: 2.0 -> 3.6V   
-> Thông thường sẽ cấp 3.3V vì nó chuẩn mức Logic (3.3V và 5V)     
- Tần số tối đa: 72Mhz    
-> 1s thực hiện 72 triệu lệnh, chứng tỏ nó có tốc độ xử lí nhanh và hiệu suất sao.
- Flash: 64KB    
-> ROM (bộ nhớ Flash): Là nơi lưu trữ mã lệnh và ở đây mã lệnh ko được vượt quá 64KB.   
- RAM: 20KB     
- Tổng số chân: 48      
- Số chân IO: 37 (Còn lại là các chân đặt biệt ko nằm ở Port nào)       

### 2. 4 khối chính của Chip        
- Khối nguồn        
-> Là nơi cấp nguồn cho chip để nó hoạt động, chân kí hiệu: VSS, VDD.       
- Khối dao động 
-> Là nơi làm cho Chip hoạt động với tần số 72Mhz, thông thường dùng thạch anh hoặc bộ dao động nội để tạo sao động, chân kí hiệu: có OSC.          
- Khối Reset        
-> Khôi phục VĐK về trạng thái ban đầu và khôi phục lại hệ thống, chân kí hiệu: RST hoặc NRST.      
- Các chân có chức năng đặc biệt        
-> Tùy vào VĐK sẽ có 1 vài chân kéo lên mức 1, đối với STM32 thì chân BOOT0 phải được nối xuống đất qua trở 10k.            

#### * Lưu ý: Trước khi nạp Code phải cấu hình BOOT0 = 0, làm thế mới bật được bộ nhớ Flash để lưu code vào đó.         

### 3. Giới thiệu GPIO 
GPIO = General Purpose Input Output: Là các chân của VĐK có thể được sử dụng với nhiều mục đích khác nhau, giúp cho VĐK có thể giao tiếp với thế giới bên ngoài.     

#### * Cấu trúc cơ bản của khối GPIO:
![](https://i.imgur.com/2fT2CyE.png)        
 Ở trong sơ đồ ta thấy có 2 khối chức năng:
 - Input Driver: Đọc các tín hiệu từ các thiết bị hoặc cảm biến bên ngoài đưa vào trong để xử lí. (Tìm hiểu ở sau).   
 - Output Driver: Điều khiển trạng thái của chân đầu ra để tương tác với thiết bị hoặc cảm biến bên ngoài.
 Tìm hiểu về khối Output Driver:        
 ![](https://i.imgur.com/azN5jTa.png)           
 ### 4. Hàm setup mức Logic cho chân & Hàm Millisecond       
- HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_Pin_PinState);     
x: Port nào?       
Pin: Chân số mấy?      
PinState: Trạng thái của chân như nào? (Reset <=> 0 & Set <=> 1).       
-> Chức năng: Cấu hình cho chân VĐK xuất ra mức Logic 0 hoặc 1.
- HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);               
-> Chức năng: Đảo mức Logic hiện tại của chân VĐK.      
- HAL_Delay(ms);        
-> Chức năng: Sau ghi gặp hàm này thì chương trình sẽ tạm dừng lại tại đây với khoảng thời gian là ms.      
##### * Lưu ý: Hàm này nên hạn chế sử dụng bởi vì khi dùng hàm này thì chương trình sẽ tạm dừng lại, ko làm được gì cả.
- HAL_Gettick();        
-> Nó trả về uint_32, cứ 1ms thì nó sẽ tăng 1 nên cứ 1s thì nó tăng 1000        
-> Chức năng: Đếm thời gian chương trình chạy, gặp hàm này thì nó sẽ trả về thời gian tại thời điểm nó được gọi.

 ### * Cấu hình cơ bản trong CubeMX để lập trình:   
- Ta nạp code qua STLink và dùng nó để Debug, 2 chân Debug nối với STLink là PA13 và PA14 nếu ta ko cấu hình thì nó như là chân GPIO       
![](https://i.imgur.com/3ey68eJ.png)        
- Có thạch anh ngoại (HSI) thì cứ dùng     
![](https://i.imgur.com/Yon3Yed.png)        
- Cấu hình nhiệm vụ các chân vào hay ra   
- Đặt tần số của HSI là tối đa 72Mhz        
------------------------------------------------------------------
## BÀI TẬP         
1. Nhấp nháy LED ở chân PC12 tần số 1Hz (500ms sáng, 500ms tắt)
2. Nhấp nháy đồng thời 2 LED. LED ở chân PC13 tần số 1Hz chân PC14 tần số 5Hz.        
(Sử dụng HAL_Gettick)






 
   


        



 