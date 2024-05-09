# Buổi 4: Ngắt ngoài

### 1. Ngắt là gì ?
Ngắt (Interrupt) có thể hiểu là 1 tín hiệu khẩn cấp gửi đến bộ vi xử lý, yêu cầu bộ vi xử lý tạm dừng các công việc đang thực hiện để nhảy đến 1 nơi khác thực hiện 1 chương trình khác. Chương trình này được gọi là phục vụ ngắt (ISR: Interrupt Service Routine). Sau khi kết thúc chương trình trong ngắt CPU sẽ quay về vị trí trước đó để thực hiện tiếp dòng lệnh còn đang dở.       
#### Hoạt động của ngắt:          
- Thực hiện lệnh từ đầu đến chỗ ngắt.           
- Dừng chương trình chính.          
- Thực hiện các lệnh trong ngắt. 
- Xong thì tiếp tục thực hiện lệnh trong chương trình chính.        
![](https://i.imgur.com/4EtRrCh.png) 
![](https://i.imgur.com/gJhCRLr.png)        
#### * Chú ý: Tín hiệu ngắt sẽ thực hiện rất nhanh vì vậy trong ngắt KO ĐƯỢC dùng DELAY.              

### 2. Ngắt ngoài.      
- Ngoắt ngoài đơn giản là ta tác động vào chân GPIO để sinh ra ngắt.      
- STM32F103 có 16 line ngắt ngoài riêng biệt, từ Line0 -> Line15. LineX sẽ chứa ngắt cho các chân Px của các Port.      
vd: Line0 sẽ chứa các chân 0 của các PortA, PortB, PortC,...
![](https://i.imgur.com/KWj3dr9.png)
#### * Chú ý: Các Line ứng với các Vector ngắt:       
- Line0 ứng EXTI line0     
- Line1 ứng EXTI line1     
- Line2 ứng EXTI line2         
- Line3 ứng EXTI line3         
- Line4 ứng EXTI line4         
- Line5 -> Line9 ứng EXTI line[9:5]        
- Line10 -> Line15 ứng EXTI line[15:10]       
#### * Lưu ý: Mỗi Line chỉ được phép có 1 chân ngắt ngoài, nghĩa là nếu ta chọn chân PA0 của Line0 làm ngắt ngoài thì tất cả các chân 0 của các Port sẽ ko được phép chọn.

### 3. Khi nào xảy ra ngắt ngoài ?
- Khi có sự chuyển đổi mức logic trên chân ngắt thì một sự kiện ngắt sẽ sinh ra. Khi đó bộ NIVC sẽ kiểm tra ngắt xảy ra ở Line nào để chạy vào chương trình ngắt tương ứng.     
- Các chế độ ngắt:
RISING (nâng lên): từ mức thấp lên mức cao.      
FALLING (rơi xuống): từ mức cao xuống mức thấp.
![](https://i.imgur.com/AeW7IJs.png)

### 4. Cấu hình ngắt trên Cube  
- Bước 1: Cấu hình chân Ngắt        
![](https://i.imgur.com/a4D8CxA.png)
- Bước 2: Cấu hình chế độ Ngắt      
![](https://i.imgur.com/cLWXvYZ.png)
- Bước 3: Cho phép ngắt và thiết lập ưu tiên Ngắt. Vào mục NIVC, tick vào Enable và có thể thiết lập ưu tiên ngắt.     
![](https://i.imgur.com/pr41OG4.png)

### 5. Ví dụ: Thiết lập ngắt cho nút nhấn.         
![](https://i.imgur.com/GsPZ3S7.png)        
Như ta thấy, Button được thiết lập ở chế độ Pull-up (chưa nhấn nút thì chân VĐK ở mức 1, nhấn nút thì 0), nó xảy ra sự chuyển đổi mức Logic nên ta có thể thiết lập Ngắt ngoài và chọn chế độ FALLING (mức cao xuống thấp).
- Cấu hình xong thì nó sẽ có thêm file "stm32f1xx.it.c", tất cả các ngắt sẽ nằm trong file này.
![](https://i.imgur.com/gkAKlLV.png)  
#### * Chú ý: Ngắt là hệ thống tự gọi chứ ko gọi ra bằng code.  
- Hàm ngắt Line0 và hàm nó gọi ra khi nhấn nút
![](https://i.imgur.com/eXVy9Gw.png)
- Trong IRQHandler(GPIO_PIN_0) nó sẽ gọi 1 hàm Call_Back()
![](https://i.imgur.com/WzrSQAu.png)
- Trong hàm Call_Back() sẽ có hàm xử lí Ngắt
![](https://i.imgur.com/uVWP8Ih.png)
#### * Từ khóa: __weak chỉ mức độ hàm ko được ưu tiên, nghĩa là khi hàm này ở chỗ khác thì nó sẽ ưu tiên gọi chỗ đó trước, nếu ko có hàm đó ở chỗ khác thì nó là sẽ được gọi.
- Cụ thể thì Ngắt ta sẽ ghi trong hàm này ở Main (ko có weak), còn nếu ko được gọi thì nó sẽ trả về hàm UNUSED() <=> chưa sử dụng Ngắt
![](https://i.imgur.com/lwMqZJq.png)
### * Nếu có nhiều chân cấu hình Ngắt thì làm sao:
Nhận thấy: Các Ngắt đều gọi chung 1 hàm chỉ khác chân Ngắt.
![](https://i.imgur.com/2dmGRmE.png)
Nên khi muốn thực hiện Ngắt ở chân nào ta chỉ cần xử lí như sau:
![](https://i.imgur.com/yxpv5Se.png)
### 6. Các mức ưu tiên Ngắt.        
Giả sử, khi có 1 chương trình đang thực hiện Ngắt mà lại có một Ngắt khác yêu cầu thì giải quyết sao?       
-> Cũng phải có ưu tiên các Ngắt.       
Có 2 loại ưu tiên Ngắt:     
- Preemption Priority: Càng thấp thì độ ưu tiên càng cao.       
- Sub Priority: Càng cao thì độ ưu tiên càng cao.
![](https://i.imgur.com/A2IQXgv.png)        
Số Bit của (Preemption Priority) + (Sub Priority) = (Priority Group)        
vd: Group 4 thì (Preemption Priority) có 4 Bit (0-15) và (Sub Priority) có 0 Bit (0).       
#### * Chú ý: Trong Cube thì nó sự setup ở Group 4 luôn
![](https://i.imgur.com/vsM1fQh.png)    
Ta sử dụng (Preemption Priority) có 0 là mức ưu tiên cao nhất, 15 là mức ưu tiên thấp nhất.
#### * Chú ý: Ta nên ưu tiên Ngắt của hệ thống nên cấu hình Ngắt các chân thì nên setup từ 1 trở đi.
### 7. Hoạt động của Ngắt lồng nhau.
- TH1: Khi có 2 Ngắt xảy ra đồng thời tại 1 thời điểm thì cái nào có mức ưu tiên cao hơn thì thực hiện trước.       
![](https://i.imgur.com/7BYSjjU.png) 
- TH2: Khi 1 Ngắt đang chạy mà có Ngắt khác cũng được gọi thì:
-- Nếu Ngắt được gọi có mức ưu tiên thấp hơn thì thực hiện Ngắt đang chạy trước và Ngắt được gọi thực hiện sau.         
-- Nếu Ngắt được gọi có mức ưu tiên cao hơn thì tạm dừng Ngắt đang chạy và thực hiện Ngắt được gọi, xong thì quay lại thực hiện tiếp Ngắt ban đầu.       
![](https://i.imgur.com/dqdtvkt.png) 

------------------------------------------------------------------
      
     
