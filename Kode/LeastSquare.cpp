#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cmath>  // Untuk fungsi std::abs dan operasi matematika lainnya

// Fungsi bantu untuk menambah hari pada tanggal (format "YYYY-MM-DD")
std::string add_days(const std::string& date_str, int days) {
    std::tm tm = {};
    // Parse string tanggal ke struct tm
    std::istringstream ss(date_str);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    
    // Tambahkan hari
    tm.tm_mday += days;
    std::mktime(&tm);  // Normalize tanggal

    // Format kembali ke string
    char buf[11];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
    return std::string(buf);
}

// Gaussian elimination sederhana untuk sistem 3x3: A * x = b
std::vector<double> solve3x3(std::vector<std::vector<double>>& A, std::vector<double>& b) {
    const int n = 3;
    // Forward elimination
    for(int i = 0; i < n; i++) {
        // Pivoting: cari baris dengan nilai absolut terbesar di kolom i
        int maxrow = i;
        for(int k = i + 1; k < n; k++) {
            if (std::abs(A[k][i]) > std::abs(A[maxrow][i])) {
                maxrow = k;
            }
        }
        std::swap(A[i], A[maxrow]);
        std::swap(b[i], b[maxrow]);

        // Eliminate baris di bawah
        for(int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for(int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }
    
    // Back substitution
    std::vector<double> x(n);
    for(int i = n - 1; i >= 0; i--) {
        double sum = b[i];
        for(int j = i + 1; j < n; j++) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }
    return x;
}

int main() {
    // Buka file data input (CSV) berisi Date,Price
    std::ifstream infile("data.csv");
    if (!infile.is_open()) {
        std::cerr << "Gagal membuka file data.csv" << std::endl;
        return 1;
    }

    std::vector<std::string> dates;
    std::vector<double> prices;
    std::string line;

    // Lewati header
    std::getline(infile, line);

    // Baca setiap baris data: "YYYY-MM-DD,price"
    while (std::getline(infile, line)) {
        std::istringstream ss(line);
        std::string date;
        double price;
        if (std::getline(ss, date, ',') && ss >> price) {
            dates.push_back(date);
            prices.push_back(price);
        }
    }
    infile.close();

    int n = prices.size();
    if (n < 3) {
        std::cerr << "Data kurang untuk regresi derajat 2" << std::endl;
        return 1;
    }

    // Hitung elemen-elemen untuk normal equations:
    //   Sum x^k dan Sum x^k * y, dengan x = 0,1,2,...,n-1
    double S0 = 0, S1 = 0, S2 = 0, S3 = 0, S4 = 0;
    double T0 = 0, T1 = 0, T2 = 0;
    for (int i = 0; i < n; i++) {
        double x = i;
        double y = prices[i];
        S0 += 1;
        S1 += x;
        S2 += x * x;
        S3 += x * x * x;
        S4 += x * x * x * x;
        T0 += y;
        T1 += x * y;
        T2 += x * x * y;
    }

    // Bentuk matriks A (3x3) dan vektor b (3)
    std::vector<std::vector<double>> A = {
        {S0, S1, S2},
        {S1, S2, S3},
        {S2, S3, S4}
    };
    std::vector<double> b = {T0, T1, T2};

    // Hitung koefisien beta (β0, β1, β2)
    std::vector<double> beta = solve3x3(A, b);

    // Tampilkan hasil koefisien di terminal, dengan simbol β
    std::cout << "Beta0 = " << beta[0] << std::endl;
    std::cout << "Beta1 = " << beta[1] << std::endl;
    std::cout << "Beta2 = " << beta[2] << std::endl;

    // Minta input: berapa hari ke depan yang akan diprediksi
    int m;
    std::cout << "Masukkan jumlah hari prediksi ke depan: ";
    std::cin >> m;
    if (m < 1) m = 1;

    // Siapkan file output CSV
    std::ofstream outfile("output.csv");
    outfile << "Date,Price,PredictedPrice" << std::endl;

    // Tulis data asli dan hasil fitting
    for (int i = 0; i < n; i++) {
        double pred = beta[0] + beta[1] * i + beta[2] * i * i;
        outfile << dates[i] << "," << prices[i] << "," << std::fixed << std::setprecision(2)
                << pred << std::endl;
    }

    // Tulis baris prediksi untuk m hari berikutnya
    for (int k = 1; k <= m; k++) {
        std::string next_date = add_days(dates.back(), k);
        int idx = n + k - 1;
        double pred = beta[0] + beta[1] * idx + beta[2] * idx * idx;
        outfile << next_date << ",," << std::fixed << std::setprecision(2) << pred << std::endl;
    }
    outfile.close();

    std::cout << "Selesai. Hasil tertulis di output.csv" << std::endl;
    return 0;
}
