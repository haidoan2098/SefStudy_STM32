# Buổi 0: Các khái niệm cơ bản trong Embedded

1. Khái niệm.
- MCU = Microcontroller = Vi điều khiển
- MPU = Microprocessor  = Vi xử lí
- CPU core = Processor core = Lõi vi xử lí      
- RAM: là nơi lưu trữ dữ liệu tạm thời cho việc xử lý và thực thi các chương trình, trong Embedded đây là không gian bộ nhớ để lưu trữ biến, bộ đệm, ngăn xếp,...           
- ROM = Bộ nhớ Flash: Là bộ nhớ ko bị mất dữ liệu khi bị mất điện, trong Embedded thì đây là nơi lưu trữ mã lệnh.       
- VDD = VCC: Đại diện cho nguồn cung cấp điện dương.      
- VSS = GND: Là điểm tham chiếu cho tất cả các tín hiệu âm và nguồn điện âm trong mạch. Nó ko phải là nguồn điện âm mà chỉ là điểm 0V.                   

####  Vi điều khiển là gì?      
Vi điều khiển thực chất là một hệ thống gồm một vi xử lí có hiệu suất đủ dùng và giá thành thấp (khác với các bộ vi xử lí đa năng trong máy tính) kết hợp với các khối ngoại vi như: bộ nhớ, module vào/ra, các module biến đổi,... (Cả con người)    
#### Vi xử lí là gì?        
Vi xử lí là một thành phần trong vi điều khiển chứa bộ xử lí trung tâm. Chức năng chính là thực hiện các phép tính toán, điều khiển hoạt động của hệ thống,... (Như cái não)            


2. Tài liệu tham khảo.
- Datasheet: Tổng quan về thiết bị và thông số kỹ thuật.
- Schematic: Sơ đồ nguyên lí của mạch, linh kiện nào, chân nào nối với chân nào.
- Reference manual: Hướng dẫn sử dụng thiết bị, các tính năng, bước thực hiện và thanh ghi.


3. Góc thắc mắc.
#### Vi điều khiển 32bit nghĩa là gì?      
- 32bit trong ngữ cảnh VĐK đề cập đến kích thướt dữ liệu của 1 VĐK. Nó biểu thị rằng, mỗi lần xử lí, VĐK có thể làm việc với dữ liệu 32 bit.        
- VĐK 32bit thường có bộ nhớ và thanh ghi có độ dài 32 bit.

 