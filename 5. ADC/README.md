# Buổi 5: ADC

 * Đặt vấn đề: Trong GPIO, mức 0 tương ứng với 0V, mức 1 tương ứng với 3.3V. Vậy ta muốn đo mức điện áp khác ngoài 2 mức này thì phải làm sao ?   
 ---> ADC ra đời                

### 1. ADC là gì ?
* ADC (Analog to Digital Converter) là bộ chuyển đổi từ tín hiệu tương tự sang tín hiệu số.      
* Các thông số của bộ ADC:
-- Voltage Reference (Vref): Điện áp tham chiếu (hay Điện áp tối đa). Điện áp dùng để làm mốc với điện áp đầu vào (Vin).        
 0 <= Vin <= Vref <= Vdd    
 ![](https://i.imgur.com/h8RPyb9.png) 
#### * Lưu ý: Thường thì ở các dòng chip khác sẽ có chân Vref nhưng STM32F103 lại ko có. Thì điện áp Vref luôn bằng điện áp của bộ Analog (Vssa - Vdda). 
#### * Lưu ý: Nguồn cấp cho VĐK khác với nguồn Analog, nhưng thường thì nguồn cấp sẽ bằng nguồn Analog luôn.      
-- Độ phân giải (n) của bộ ADC: là số bit dùng để chứa hết các giá trị sau khi chuyển đổi của bộ ADC.           
ví dụ: Độ phân giải của bộ ADC STM32F103 là n = 12 thì nó sẽ chứa các giá trị từ 0 -> 2^12-1 = 4095.            
Nếu như ta đọc được giá trị của ADC = 400 thì điện áp đầu vào Vin bằng bao nhiêu?            
![](https://i.imgur.com/dzpG0x8.png)        
#### * Chú ý: Công thức tính điện áp đầu vào ADC    
![](https://i.imgur.com/dc6VIpG.png)         
#### * Tóm tắt: 
![](https://i.imgur.com/KNVwgmU.png)   

### 2. Cấu hình ADC trog Cube.      
* Số bộ ADC: 2      
* Số kênh ADC: 10 kênh, các kênh từ chân A0->A7, B0, B1.   
* Bước 1: Chọn bộ ADC và tick chọn kênh.             
![](https://i.imgur.com/l5A7OR6.png)
* Bước 2: Chọn Channel      
![](https://i.imgur.com/mjpyBKu.png)

### 3. Các hàm quan trọng.      
* HAL_ADC_Start(): Kích hoạt thiết bị ngoại vi ADC và bắt đầu chuyển đổi.   
-- Hàm gốc: HAL_ADC_Start(ADC_HandleTypeDef* hadc)      
Nghĩa là mình có 2 kênh ADC nên nó ko biết cái nào, nên khi gọi hàm này ta phải bỏ vào kênh nào. (Này đã được CubeMX tạo ra ngay khi chọn kênh).        
![](https://i.imgur.com/xqYWADr.png)  
--> HAL_ADC_Start(&hadc1);        
* HAL_ADC_PollForConversion(): Đợi quá trình chuyển đổi ADC hoàn tất.       
-- Hàm gốc: HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)        
Timeout là gì? Chuyển đổi từ tín hiệu tương tự sang số sẽ mất 1 khoảng thời gian, nhưng nếu như trong quá trình chuyển đổi bị lỗi thì nó sẽ dừng ở đây mãi -> Timeout là khoảng thời gian mà nếu như nó chuyển đổi quá thời gian thì nó sẽ out ra làm việc khác. (Time tính theo ms)      
--> HAL_ADC_PollForConversion(&hacd1, 1);
* HAL_ADC_GetValue(): Xuất ra giá trị chuyển đổi.       
-- Hàm gốc: uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef* hadc)      
Tương tự nhưng nó trả về 1 giá trị uint32_t     
--> uint32_t adc = HAL_ADC_GetValue(&hacd1);      
* HAL_ADC_Stop(): Dừng chuyển đổi và tắt thiết bị ngoại vi ADC      
-- Hàm gốc: HAL_ADC_Stop(ADC_HandleTypeDef* hadc)       
--> HAL_ADC_Stop(&hacd1)
### 4. Các chú ý.
* Chân chưa cấu hình gì cả thì nó ở chế độ Floating (Ko xác định), thì giá trị ADC nó sẽ nhảy loạn xạ.      
* Ở 0V thì ta đo ADC = 0, nhưng khi 3.3V thì ADC = 4036 - 4039 trong khi lý thuyết là 4095 ? Tại sao?
![](https://i.imgur.com/DSk9A92.png)  
### * Lý do: Lỗi phần cứng bên trong, nhà sản xuất cũng có nói
![](https://i.imgur.com/pyD3Q09.png)        
Tóm tắt lại như sau: Hiệu suất của ADC giảm do các tụ điện bên xong. Ngta cũng lưu ý là nên bật mode Calibration sau mỗi lần bật nguồn (sau khi vô hàm main)        
* HAL_ADCEx_Calibration_Start(): Tự hiệu chỉnh ADC
--> HAL_ADCEx_Calibration_Start(&hadc1);        
Sau khi có HAL_ADCEx_Calibration_Start() thì nó đã chính xác        
![](https://i.imgur.com/Zs0hopX.png)

------------------------------------------------------------------
   
     
