
#include <fstream>
#include <iostream>

void SaveHistogramsToTxt() {
    // ROOT dosyasının adı
    const char* rootFileName = "case1_E2_TB1.root";

    // ROOT dosyasını aç
    TFile *file = TFile::Open(rootFileName, "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Hata: Dosya açılamadı veya bozuk: " << rootFileName << std::endl;
        return;
    }

    std::cout << "Dosya başarıyla açıldı: " << rootFileName << std::endl;

    // Dosyadaki tüm anahtarları döngüyle gezin
    TIter nextKey(file->GetListOfKeys());
    TKey *key;

    while ((key = (TKey*)nextKey())) {
        // Nesneyi oku
        TObject *obj = key->ReadObj();

        // Histogram mı kontrol et
        if (obj->InheritsFrom("TH1")) {
            TH1 *hist = (TH1*)obj;

            // Histogramın adı
            std::string histName = hist->GetName();

            // Histogramı kaydetmek için dosya adı oluştur
            std::string fileName = histName + ".txt";

            // .txt dosyasını aç
            std::ofstream outFile(fileName);
            if (!outFile.is_open()) {
                std::cerr << "Hata: " << fileName << " dosyası açılamadı!" << std::endl;
                continue;
            }

            // Histogram bin bilgilerini yaz
            outFile << "Bin Center\tBin Content\tBin Error\n";
            for (int i = 1; i <= hist->GetNbinsX(); ++i) {
                double binCenter = hist->GetBinCenter(i);
                double binContent = hist->GetBinContent(i);
                double binError = hist->GetBinError(i);
                outFile << binCenter << "\t" << binContent << "\t" << binError << "\n";
            }

            outFile.close();
            std::cout << histName << " histogramı " << fileName << " dosyasına kaydedildi." << std::endl;
        }
    }

    // ROOT dosyasını kapat
    file->Close();
    delete file;

    std::cout << "Tüm histogramlar başarıyla kaydedildi." << std::endl;
}
