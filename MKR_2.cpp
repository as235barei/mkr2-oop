#include <iostream>
#include <vector>
#include <string>

// Попереднє оголошення класів
class ComputerGadget;
class VoiceRecorder;

// Структура віртуальної таблиці для класу ComputerGadget
struct ComputerGadgetVTable {
	void (ComputerGadget::* getInfo)() const;
};

// Структура віртуальної таблиці для класу VoiceRecorder
struct VoiceRecorderVTable {
	void (VoiceRecorder::* getInfo)() const;
};

// Базовий клас Комп'ютерний гаджет
class ComputerGadget {
protected:
	std::string brand;        // Бренд гаджета
	std::string model;        // Модель гаджета
	std::string color;        // Колір гаджета
	double price;             // Ціна гаджета
	double weight;            // Вага гаджета в грамах
	double batteryLife;       // Час автономної роботи в годинах
	bool isOn;                // Стан гаджета (увімкнено/вимкнено)

	// Покажчик на віртуальну таблицю
	ComputerGadgetVTable* vTablePtr;

public:
	// Конструктор з параметрами
	ComputerGadget(const std::string& brand, const std::string& model, double price,
		const std::string& color, double weight, double batteryLife)
		: brand(brand), model(model), price(price), color(color), weight(weight), batteryLife(batteryLife), isOn(false) {
		// Ініціалізація покажчика на віртуальну таблицю
		vTablePtr = getVTablePtr();
	}

	// Віртуальний деструктор
	virtual ~ComputerGadget() = default;

	// Віртуальний метод для отримання інформації про гаджет
	virtual void getInfo() const {
		std::cout << "Brand: " << brand << ", Model: " << model << ", Price: " << price
			<< ", Color: " << color << ", Weight: " << weight << "g"
			<< ", Battery Life: " << batteryLife << "h"
			<< ", State: " << (isOn ? "On" : "Off") << "\n" << std::endl;
	}

	// Методи для роботи з атрибутами
	void setColor(const std::string& color) {
		this->color = color;
	}

	std::string getColor() const {
		return color;
	}

	void setWeight(double weight) {
		this->weight = weight;
	}

	double getWeight() const {
		return weight;
	}

	void setBatteryLife(double batteryLife) {
		this->batteryLife = batteryLife;
	}

	double getBatteryLife() const {
		return batteryLife;
	}

	double getPrice() const {
		return price;
	}

	// Методи для ввімкнення та вимкнення гаджета
	void turnOn() {
		isOn = true;
		std::cout << "The gadget is now ON.\n";
	}

	void turnOff() {
		isOn = false;
		std::cout << "The gadget is now OFF.\n";
	}

	bool getIsOn() const {
		return isOn;
	}

	// Статичний метод для відображення загальної інформації
	static void displayGeneralInfo() {
		std::cout << "___This is a general computer gadget.___ \n" << std::endl;
	}

	// Метод для отримання покажчика на віртуальну таблицю
	ComputerGadgetVTable* getVTablePtr() {
		static ComputerGadgetVTable vTable = {
			&ComputerGadget::getInfo
		};
		return &vTable;
	}

	// Getter for vTablePtr
	ComputerGadgetVTable* getVTable() const {
		return vTablePtr;
	}
};

// Клас диктофон
class VoiceRecorder : public ComputerGadget {
private:
	std::string microphoneType;      // Тип мікрофона
	std::string recordingFormat;     // Формат запису
	std::string additionalFeatures;  // Додаткові функції
	double maxRecordingTime;         // Максимальний час запису в годинах

	// Покажчик на віртуальну таблицю
	VoiceRecorderVTable* vTablePtr;

public:
	VoiceRecorder(const std::string& brand, const std::string& model, double price,
		const std::string& color, double weight, double batteryLife,
		const std::string& microphoneType, const std::string& recordingFormat,
		double maxRecordingTime, const std::string& additionalFeatures)
		: ComputerGadget(brand, model, price, color, weight, batteryLife),
		microphoneType(microphoneType), recordingFormat(recordingFormat),
		maxRecordingTime(maxRecordingTime), additionalFeatures(additionalFeatures) {
		// Ініціалізація покажчика на віртуальну таблицю
		vTablePtr = getVTablePtr();
	}

	// Методи для роботи з атрибутами
	void setMicrophoneType(const std::string& microphoneType) {
		this->microphoneType = microphoneType;
	}

	std::string getMicrophoneType() const {
		return microphoneType;
	}

	void setRecordingFormat(const std::string& recordingFormat) {
		this->recordingFormat = recordingFormat;
	}

	std::string getRecordingFormat() const {
		return recordingFormat;
	}

	void setMaxRecordingTime(double maxRecordingTime) {
		this->maxRecordingTime = maxRecordingTime;
	}

	double getMaxRecordingTime() const {
		return maxRecordingTime;
	}

	void setAdditionalFeatures(const std::string& additionalFeatures) {
		this->additionalFeatures = additionalFeatures;
	}

	std::string getAdditionalFeatures() const {
		return additionalFeatures;
	}

	// Метод для запису
	void record(const std::string& message) {
		if (isOn) {
			std::cout << "Recording: ----->" << message << "<-----" << "\n";
		}
		else {
			std::cout << "The gadget is OFF. Please turn it on to record.\n";
		}
	}

	// Перевантаження операції виведення
	friend std::ostream& operator<<(std::ostream& os, const VoiceRecorder& vr) {
		os << "Brand: " << vr.brand << ", Model: " << vr.model << ", Price: " << vr.price
			<< ", Color: " << vr.color << ", Weight: " << vr.weight << "g"
			<< ", Battery Life: " << vr.batteryLife << "h"
			<< ", Microphone Type: " << vr.microphoneType
			<< ", Recording Format: " << vr.recordingFormat
			<< ", Max Recording Time: " << vr.maxRecordingTime << "h"
			<< ", Additional Features: " << vr.additionalFeatures
			<< ", State: " << (vr.isOn ? "On" : "Off") << "\n" << std::endl;
		return os;
	}

	// Віртуальний метод для отримання інформації про диктофон
	void getInfo() const override {
		std::cout << "Voice Recorder Info -> " << "Brand: " << brand << ", Model: " << model << ", Price: " << price
			<< ", Color: " << color << ", Weight: " << weight << "g"
			<< ", Battery Life: " << batteryLife << "h"
			<< ", Microphone Type: " << microphoneType
			<< ", Recording Format: " << recordingFormat
			<< ", Max Recording Time: " << maxRecordingTime << "h"
			<< ", Additional Features: " << additionalFeatures
			<< ", State: " << (isOn ? "On" : "Off") << "\n" << std::endl;
	}

	// Метод для отримання покажчика на віртуальну таблицю
	VoiceRecorderVTable* getVTablePtr() {
		static VoiceRecorderVTable vTable = {
			&VoiceRecorder::getInfo
		};
		return &vTable;
	}

	// Getter for vTablePtr
	VoiceRecorderVTable* getVTable() const {
		return vTablePtr;
	}
};

// Контейнерний клас для роботи з об'єктами ComputerGadget
class GadgetContainer {
private:
	std::vector<ComputerGadget*> gadgets;

public:
	// Додавання об'єкта до контейнера
	void addGadget(ComputerGadget* gadget) {
		gadgets.push_back(gadget);
	}

	// Видалення об'єкта з контейнера за індексом
	void removeGadget(size_t index) {
		if (index < gadgets.size()) {
			delete gadgets[index];
			gadgets.erase(gadgets.begin() + index);
		}
	}

	// Пошук об'єкта за індексом
	ComputerGadget* getGadget(size_t index) const {
		if (index < gadgets.size()) {
			return gadgets[index];
		}
		else {
			std::cout << "Gadget not found at index " << index << ".\n";
			return nullptr;
		}
	}

	// Відображення вмісту контейнера
	void displayAll() const {
		for (const auto& gadget : gadgets) {
			(gadget->*gadget->getVTable()->getInfo)();
		}
	}

	// Деструктор для очищення пам'яті
	~GadgetContainer() {
		for (auto& gadget : gadgets) {
			delete gadget;
		}
	}
};

// Основна функція для демонстрації роботи
int main() {
	// Створення об'єктів
	const ComputerGadget* cg1 = new ComputerGadget("GenericBrand", "ModelX", 100.0, "Black", 150.0, 10.0);
	VoiceRecorder* vr1 = new VoiceRecorder("Sony", "ICD-PX470", 79.99, "Silver", 74.0, 20.0, "Omnidirectional", "MP3", 10.0, "Wi-Fi, Bluetooth");
	VoiceRecorder* vr2 = new VoiceRecorder("Olympus", "VN-7200", 49.99, "Black", 60.0, 25.0, "Lavalier", "WAV", 8.0, "Memory Card Slot");

	// Використання контейнерного класу
	GadgetContainer container;
	container.addGadget(const_cast<ComputerGadget*>(cg1));
	container.addGadget(vr1);
	container.addGadget(vr2);

	// Демонстрація вмісту контейнера
	std::cout << "----------All Gadgets in Container:----------" << std::endl;
	container.displayAll();

	// Виклик статичного методу
	ComputerGadget::displayGeneralInfo();

	// Демонстрація перевантаженої операції виведення
	std::cout << "----------Voice Recorder Details:----------" << std::endl;
	std::cout << *vr1;
	std::cout << *vr2;

	// Зміна атрибутів
	std::cout << "----------Updating attributes of the voice recorders----------" << std::endl;
	vr1->setColor("Red");
	vr1->setWeight(70.0);
	vr1->setBatteryLife(15.0);
	vr1->setMicrophoneType("Lavalier");
	vr1->setRecordingFormat("WAV");
	vr1->setMaxRecordingTime(12.0);
	vr1->setAdditionalFeatures("Wi-Fi, Bluetooth, Noise Reduction");

	vr2->setColor("Gray");
	vr2->setWeight(65.0);
	vr2->setBatteryLife(22.0);
	vr2->setMicrophoneType("Omnidirectional");
	vr2->setRecordingFormat("MP3");
	vr2->setMaxRecordingTime(9.0);
	vr2->setAdditionalFeatures("Memory Card Slot, Voice Activation");

	// Повторна демонстрація атрибутів після змін
	std::cout << *vr1;
	std::cout << *vr2;

	// Увімкнення та вимкнення гаджетів
	vr1->turnOn();
	vr1->record("'This is a test recording: Hello World!'");
	vr1->turnOff();
	vr1->record("'This should not be recorded: Hello World!'");

	// Пошук об'єкта за індексом, який існує
	std::cout << "\n----------Searching for Gadget at Index 1:----------" << std::endl;
	ComputerGadget* searchedGadget = container.getGadget(1);
	if (searchedGadget) {
		(searchedGadget->*searchedGadget->getVTable()->getInfo)();
	}

	// Пошук об'єкта за індексом, який не існує
	std::cout << "----------Searching for Gadget at Index 3:----------" << std::endl;
	ComputerGadget* searchedGadgetAgain = container.getGadget(3);
	if (searchedGadgetAgain) {
		(searchedGadgetAgain->*searchedGadgetAgain->getVTable()->getInfo)();
	}

	// Видалення об'єкта з контейнера
	std::cout << "\n!!!Removing an object from a container!!!\n" << std::endl;
	container.removeGadget(0);

	// Повторне відображення вмісту контейнера після видалення
	std::cout << "----------Gadgets in Container after removal:----------" << std::endl;
	container.displayAll();

	return 0;
}
