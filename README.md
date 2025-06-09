# Prediksi Harga Saham Menggunakan LSR

### Oleh: Reyhan Ahnaf Deannova  
### NPM: 2306267100

---

## Deskripsi Singkat

Program ini dibuat untuk memprediksi harga berdasarkan data historis yang tersimpan dalam file `data.csv`. Metode yang digunakan adalah **regresi polinomial derajat dua (kuadrat)**, yang dihitung menggunakan metode **least squares fitting**. Program ini ditulis dalam bahasa C++ dan menghasilkan file `output.csv` berisi prediksi harga untuk sejumlah hari ke depan.

---

## Fitur Utama

- Membaca data historis harga dari file CSV (`data.csv`) dengan format `Date,Price`.
- Menghitung koefisien model regresi kuadrat secara manual menggunakan eliminasi Gauss.
- Memprediksi harga untuk `m` hari ke depan berdasarkan tren historis.
- Menyimpan hasil dalam file `output.csv` berisi data asli dan hasil prediksi.

---

## Format File Input (`data.csv`)

File CSV harus memiliki format sebagai berikut:
Date,Price
2024-01-01,1000
2024-01-02,1015
...


- Baris pertama adalah header.
- Baris-baris berikutnya berisi tanggal dalam format `YYYY-MM-DD` dan harga (angka desimal atau bulat).
- Minimal 3 baris data diperlukan untuk menjalankan model regresi kuadrat.

---

## Format File Output (`output.csv`)

Program akan menghasilkan file `output.csv` dengan format berikut:
Date,Price,PredictedPrice
2024-01-01,1000,998.50
2024-01-02,1015,1012.34
...

- Kolom `PredictedPrice` diisi dengan hasil model regresi.
- Baris-baris tanpa `Price` menunjukkan hasil prediksi untuk hari-hari ke depan.

---

## Cara Menjalankan Program

### 1. Kompilasi Program

Gunakan compiler C++ seperti `g++`. Jalankan perintah berikut di terminal:

```bash
g++ -o LeastSquare LeastSquare.cpp
```

Perintah ini akan menghasilkan file eksekusi bernama `LeastSquare`.

### 2. Siapkan File `data.csv`

Pastikan file `data.csv` berada dalam folder yang sama dengan file eksekusi dan berisi data sesuai format di atas.

### 3. Jalankan Program

Jalankan program menggunakan perintah:

```bash
./LeastSquare
```

Jika menggunakan Windows:

```bash
LeastSquare.exe
```

Program akan meminta Anda memasukkan jumlah hari yang ingin diprediksi:

```
Masukkan jumlah hari prediksi ke depan: 5
```

Masukkan angka (misalnya 5), lalu tekan Enter.

### 4. Lihat Hasil

Program akan menghasilkan file `output.csv` di direktori yang sama, yang dapat dibuka dengan Excel, Google Sheets, atau text editor untuk melihat hasil prediksi.

---

## Penjelasan Teknis

* Model regresi kuadrat berbentuk:

  $$
  y = \beta_0 + \beta_1 \cdot x + \beta_2 \cdot x^2
  $$

  di mana `x` adalah indeks waktu (0, 1, 2, ...) dan `y` adalah harga.

* Koefisien $\beta_0$, $\beta_1$, dan $\beta_2$ dihitung dengan menyusun sistem persamaan normal, kemudian diselesaikan menggunakan metode **eliminasi Gauss**.

* Fungsi `add_days()` digunakan untuk menghitung tanggal ke depan berdasarkan tanggal terakhir di data historis.

---

## Ketentuan

* File input `data.csv` wajib ada dan memenuhi format yang sesuai.
* Program tidak memperhitungkan hari libur atau akhir pekan.
* Model regresi kuadrat cocok untuk pola tren yang mulus, dan kurang cocok untuk fluktuasi tajam.

---

## Contoh

Misalnya isi `data.csv` adalah:

```
Date,Price
2024-01-01,1000
2024-01-02,1020
2024-01-03,1045
```

Jika Anda memasukkan `3` hari prediksi, maka `output.csv` akan berisi:

```
Date,Price,PredictedPrice
2024-01-01,1000,1000.00
2024-01-02,1020,1020.00
2024-01-03,1045,1045.00
2024-01-04,,1075.00
2024-01-05,,1110.00
2024-01-06,,1150.00
```

---
