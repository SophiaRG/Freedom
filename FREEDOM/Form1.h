#pragma once

// uncomment to execute the rk1-utils:
//    #include "rk1_Utils_demo.h"  // shows how the rk1-utils can be used

#include "Header1.h"
#include "Header2.h"
#include "logic.h"

namespace CppCLRWinFormsProject {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  /// <summary>
  /// Summary for Form1
  /// </summary>
  public ref class Form1 : public System::Windows::Forms::Form
  {
  public:
    Form1(void)
    {
      InitializeComponent();
      //
      //TODO: Add the constructor code here
      board = gcnew Board(pictureBox1);

      // uncomment to execute the rk1-utils:
      //    N_rk1_Utils_demo::execute(); // shows how the rk1-utils can be used

    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~Form1()
    {
      if (components)
      {
        delete components;
      }
    }
  private: System::Windows::Forms::PictureBox^ pictureBox1;
         Board^ board;

  private: System::Windows::Forms::Button^ button2;
  protected:





  protected:

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
        this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
        this->button2 = (gcnew System::Windows::Forms::Button());
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
        this->SuspendLayout();
        // 
        // pictureBox1
        // 
        this->pictureBox1->Location = System::Drawing::Point(88, 60);
        this->pictureBox1->Name = L"pictureBox1";
        this->pictureBox1->Size = System::Drawing::Size(1305, 1054);
        this->pictureBox1->TabIndex = 0;
        this->pictureBox1->TabStop = false;
        this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::pictureBox1_Paint);
        this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseClick);
        // 
        // button2
        // 
        this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
            | System::Windows::Forms::AnchorStyles::Left)
            | System::Windows::Forms::AnchorStyles::Right));
        this->button2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
        this->button2->BackColor = System::Drawing::Color::Snow;
        this->button2->Font = (gcnew System::Drawing::Font(L"Roboto Medium", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
            static_cast<System::Byte>(0)));
        this->button2->ForeColor = System::Drawing::Color::MidnightBlue;
        this->button2->Location = System::Drawing::Point(1198, 406);
        this->button2->Name = L"button2";
        this->button2->Size = System::Drawing::Size(195, 174);
        this->button2->TabIndex = 2;
        this->button2->Text = L"Finish game";
        this->button2->UseVisualStyleBackColor = false;
        this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
        // 
        // Form1
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->BackColor = System::Drawing::Color::Lavender;
        this->ClientSize = System::Drawing::Size(1545, 1126);
        this->Controls->Add(this->button2);
        this->Controls->Add(this->pictureBox1);
        this->Cursor = System::Windows::Forms::Cursors::Hand;
        this->Margin = System::Windows::Forms::Padding(4);
        this->Name = L"Form1";
        this->Text = L"Form1";
        this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
        (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
        this->ResumeLayout(false);

    }
#pragma endregion

   // You can call the functions at a button click. If you prefer, 
    // you can call them by clicking a menu item.

  private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
      board->DrawBoard();
  }
  private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
      board->MakeMove(e);
  }
  private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
      board->FinishGame();
  }
  private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
  }

}; // end of class Form1
} // end of namespace CppCLRWinFormsProject

