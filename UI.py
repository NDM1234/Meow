import ctypes
import os
import sys
from PySide6.QtWidgets import (
    QApplication,
    QComboBox,
    QFileDialog,
    QHBoxLayout,
    QLabel,
    QPushButton,
    QStackedWidget,
    QTextEdit,
    QVBoxLayout,
    QWidget,
)


class MeowApp(QWidget):

  def __init__(self):
    super().__init__()
    self.load_dll()
    self.initUI()

  def load_dll(self):
    # Load file DLL từ thư mục hiện tại
    dll_path = os.path.join(os.path.dirname(__file__), "meow_encoder.dll")
    try:
      self.meow_lib = ctypes.CDLL(dll_path)

      # --- KHAI BÁO ARGTYPES CHO 4 HÀM C ---
      self.meow_lib.meow_chuoi.argtypes = [
          ctypes.c_char_p,
          ctypes.c_char_p,
          ctypes.c_int,
      ]
      self.meow_lib.meow_file.argtypes = [
          ctypes.c_char_p,
          ctypes.c_char_p,
          ctypes.c_int,
      ]
      self.meow_lib.dich_chuoi.argtypes = [
          ctypes.c_char_p,
          ctypes.c_char_p,
          ctypes.c_int,
      ]
      self.meow_lib.dich_file.argtypes = [
          ctypes.c_char_p,
          ctypes.c_char_p,
          ctypes.c_int,
      ]
    except Exception as e:
      print(f"⚠️ Không thể load file DLL: {e}")
      sys.exit(1)

  def initUI(self):
    self.setWindowTitle(
        "🐾 Mèo Bánh Translate 🐾"
    )
    self.resize(850, 500)

    main_layout = QVBoxLayout()

    # --- 1. THANH CÔNG CỤ TRÊN ---
    top_bar_layout = QHBoxLayout()

    self.mode_combo = QComboBox()
    self.mode_combo.addItems(
        ["📝 Chế độ: Nhập Chuỗi", "📁 Chế độ: Chọn File"]
    )
    self.mode_combo.currentIndexChanged.connect(self.switch_input_mode)
    top_bar_layout.addWidget(self.mode_combo)

    self.direction_combo = QComboBox()
    self.direction_combo.addItems([
        "Mã hóa",
        "Giải mã",
    ])
    top_bar_layout.addWidget(self.direction_combo)

    top_bar_layout.addStretch()
    main_layout.addLayout(top_bar_layout)

    # --- 2. KHU VỰC TRUNG TÂM (2 CỘT) ---
    center_layout = QHBoxLayout()

    # Cột trái (Input / Chọn file)
    left_layout = QVBoxLayout()
    left_label = QLabel("Văn bản gốc / Nguồn")
    left_layout.addWidget(left_label)

    self.input_stack = QStackedWidget()

    self.text_input = QTextEdit()
    self.text_input.setPlaceholderText("Nhập nội dung cần xử lý ở đây...")
    self.input_stack.addWidget(self.text_input)

    self.file_btn = QPushButton(
        "📂 Nhấn để chọn file từ máy tính\n(Hỗ trợ chọn nhiều file)"
    )
    self.file_btn.setStyleSheet(
        "border: 2px dashed #ffb703; border-radius: 8px; background-color:"
        " #fffcf2; font-weight: bold; color: #d48301; padding: 25px;"
    )
    self.file_btn.clicked.connect(self.open_file_dialog)
    self.input_stack.addWidget(self.file_btn)

    left_layout.addWidget(self.input_stack)

    self.file_info_label = QLabel("")
    self.file_info_label.setStyleSheet("color: gray; font-style: italic;")
    left_layout.addWidget(self.file_info_label)

    center_layout.addLayout(left_layout, stretch=1)

    # Nút đảo chiều giữa
    middle_layout = QVBoxLayout()
    middle_layout.addStretch()
    self.swap_btn = QPushButton("⇄")
    self.swap_btn.setFixedSize(40, 40)
    self.swap_btn.setStyleSheet(
        "font-size: 18px; font-weight: bold; border-radius: 20px;"
        " background-color: #e9ecef; border: 1px solid #ced4da;"
    )
    self.swap_btn.clicked.connect(self.swap_direction)
    middle_layout.addWidget(self.swap_btn)
    middle_layout.addStretch()
    center_layout.addLayout(middle_layout)

    # Cột phải (Output)
    right_layout = QVBoxLayout()
    right_label = QLabel("Kết quả / Trạng thái")
    right_layout.addWidget(right_label)

    self.output_text = QTextEdit()
    self.output_text.setReadOnly(True)
    self.output_text.setPlaceholderText("Kết quả sẽ hiển thị ở đây...")
    right_layout.addWidget(self.output_text)

    dummy_label = QLabel("")
    right_layout.addWidget(dummy_label)

    center_layout.addLayout(right_layout, stretch=1)
    main_layout.addLayout(center_layout)

    # --- 3. NÚT THỰC HIỆN ---
    self.translate_btn = QPushButton("🚀 THỰC HIỆN NGAY 🐾")
    self.translate_btn.setStyleSheet(
        "background-color: #3a86ff; color: white; font-weight: bold; font-size:"
        " 15px; padding: 12px; border-radius: 6px;"
    )
    self.translate_btn.clicked.connect(self.execute_translation)
    main_layout.addWidget(self.translate_btn)

    self.setLayout(main_layout)
    self.selected_files = []

  def switch_input_mode(self, index):
    self.input_stack.setCurrentIndex(index)
    if index == 1:
      self.file_info_label.setText("Chưa có file nào được chọn.")
    else:
      self.file_info_label.setText("")

  def open_file_dialog(self):
    files, _ = QFileDialog.getOpenFileNames(
        self, "Chọn file", "", "Text Files (*.txt);;All Files (*)"
    )
    if files:
      self.selected_files = files
      file_names = ", ".join([f.split("/")[-1] for f in files])
      self.file_info_label.setText(f"Đã chọn {len(files)} file: {file_names}")

  def swap_direction(self):
    current_idx = self.direction_combo.currentIndex()
    new_idx = 1 if current_idx == 0 else 0
    self.direction_combo.setCurrentIndex(new_idx)

  def execute_translation(self):
    mode = self.mode_combo.currentIndex()  # 0: Chuỗi, 1: File
    direction = self.direction_combo.currentIndex()  # 0: Mã hóa, 1: Giải mã

    if mode == 0:
      # --- XỬ LÝ CHUỖI ---
      text = self.text_input.toPlainText()
      if not text.strip():
        self.output_text.setText("⚠️ Cậu ơi, hãy nhập nội dung văn bản đã nhé!")
        return

      # Cấp phát buffer an toàn trên RAM nhận kết quả từ C
      output_buffer = ctypes.create_string_buffer(8192)

      if direction == 0:
        self.meow_lib.meow_chuoi(
            text.encode("utf-8"), output_buffer, len(output_buffer)
        )
      else:
        self.meow_lib.dich_chuoi(
            text.encode("utf-8"), output_buffer, len(output_buffer)
        )

      # Giải mã bytes từ C về string hiển thị lên UI
      result = output_buffer.value.decode("utf-8", errors="ignore")
      self.output_text.setText(result)

    else:
      # --- XỬ LÝ FILE ---
      if not self.selected_files:
        self.output_text.setText(
            "⚠️ Cậu chưa chọn file nào cả! Hãy bấm chọn file bên trái."
        )
        return

      success_count = 0
      status_logs = []

      for file_path in self.selected_files:
        msg_buffer = ctypes.create_string_buffer(1024)

        if direction == 0:
          self.meow_lib.meow_file(
              file_path.encode("utf-8"), msg_buffer, len(msg_buffer)
          )
        else:
          self.meow_lib.dich_file(
              file_path.encode("utf-8"), msg_buffer, len(msg_buffer)
          )

        status_logs.append(msg_buffer.value.decode("utf-8", errors="ignore"))
        success_count += 1

      summary = (
          f"🐾 Đã xử lý xong {success_count} file!\n\n" + "\n".join(status_logs)
      )
      self.output_text.setText(summary)


if __name__ == "__main__":
  app = QApplication(sys.argv)
  window = MeowApp()
  window.show()
  sys.exit(app.exec())