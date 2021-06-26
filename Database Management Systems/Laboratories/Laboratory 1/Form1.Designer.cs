
namespace Lab1
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.connect_button = new System.Windows.Forms.Button();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.id_box = new System.Windows.Forms.TextBox();
            this.name_box = new System.Windows.Forms.TextBox();
            this.sname_box = new System.Windows.Forms.TextBox();
            this.flength_box = new System.Windows.Forms.TextBox();
            this.add_button = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.fweight_box = new System.Windows.Forms.TextBox();
            this.color_box = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.behaviour_box = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.delete_button = new System.Windows.Forms.Button();
            this.update_button = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // connect_button
            // 
            this.connect_button.Location = new System.Drawing.Point(795, 12);
            this.connect_button.Name = "connect_button";
            this.connect_button.Size = new System.Drawing.Size(142, 60);
            this.connect_button.TabIndex = 0;
            this.connect_button.Text = "Connect";
            this.connect_button.UseVisualStyleBackColor = true;
            this.connect_button.Click += new System.EventHandler(this.connect_button_Click);
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(12, 12);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.ReadOnly = true;
            this.dataGridView1.RowHeadersWidth = 62;
            this.dataGridView1.RowTemplate.Height = 33;
            this.dataGridView1.Size = new System.Drawing.Size(777, 272);
            this.dataGridView1.TabIndex = 1;
            this.dataGridView1.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            // 
            // dataGridView2
            // 
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(12, 290);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.ReadOnly = true;
            this.dataGridView2.RowHeadersWidth = 62;
            this.dataGridView2.RowTemplate.Height = 33;
            this.dataGridView2.Size = new System.Drawing.Size(1408, 206);
            this.dataGridView2.TabIndex = 2;
            this.dataGridView2.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView2_CellContentClick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(795, 93);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(27, 25);
            this.label1.TabIndex = 4;
            this.label1.Text = "id";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(795, 167);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(66, 25);
            this.label2.TabIndex = 5;
            this.label2.Text = "Sname";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(795, 128);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(56, 25);
            this.label3.TabIndex = 6;
            this.label3.Text = "name";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(795, 204);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(72, 25);
            this.label4.TabIndex = 7;
            this.label4.Text = "fLength";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // id_box
            // 
            this.id_box.Location = new System.Drawing.Point(872, 93);
            this.id_box.Name = "id_box";
            this.id_box.Size = new System.Drawing.Size(174, 31);
            this.id_box.TabIndex = 8;
            this.id_box.Text = "0";
            this.id_box.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // name_box
            // 
            this.name_box.Location = new System.Drawing.Point(872, 130);
            this.name_box.Name = "name_box";
            this.name_box.Size = new System.Drawing.Size(174, 31);
            this.name_box.TabIndex = 9;
            this.name_box.Text = "name";
            // 
            // sname_box
            // 
            this.sname_box.Location = new System.Drawing.Point(872, 167);
            this.sname_box.Name = "sname_box";
            this.sname_box.ReadOnly = true;
            this.sname_box.Size = new System.Drawing.Size(174, 31);
            this.sname_box.TabIndex = 10;
            this.sname_box.Text = "Sname";
            // 
            // flength_box
            // 
            this.flength_box.Location = new System.Drawing.Point(872, 204);
            this.flength_box.Name = "flength_box";
            this.flength_box.Size = new System.Drawing.Size(174, 31);
            this.flength_box.TabIndex = 11;
            this.flength_box.Text = "fLength";
            // 
            // add_button
            // 
            this.add_button.Location = new System.Drawing.Point(872, 250);
            this.add_button.Name = "add_button";
            this.add_button.Size = new System.Drawing.Size(112, 34);
            this.add_button.TabIndex = 12;
            this.add_button.Text = "Add";
            this.add_button.UseVisualStyleBackColor = true;
            this.add_button.Click += new System.EventHandler(this.add_button_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(1080, 96);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(74, 25);
            this.label5.TabIndex = 13;
            this.label5.Text = "fWeight";
            // 
            // fweight_box
            // 
            this.fweight_box.Location = new System.Drawing.Point(1177, 93);
            this.fweight_box.Name = "fweight_box";
            this.fweight_box.Size = new System.Drawing.Size(174, 31);
            this.fweight_box.TabIndex = 14;
            this.fweight_box.Text = "fWeight";
            // 
            // color_box
            // 
            this.color_box.Location = new System.Drawing.Point(1177, 130);
            this.color_box.Name = "color_box";
            this.color_box.Size = new System.Drawing.Size(174, 31);
            this.color_box.TabIndex = 16;
            this.color_box.Text = "color";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(1080, 133);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(52, 25);
            this.label6.TabIndex = 15;
            this.label6.Text = "color";
            // 
            // behaviour_box
            // 
            this.behaviour_box.Location = new System.Drawing.Point(1177, 167);
            this.behaviour_box.Name = "behaviour_box";
            this.behaviour_box.Size = new System.Drawing.Size(174, 31);
            this.behaviour_box.TabIndex = 18;
            this.behaviour_box.Text = "behaviour";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(1080, 170);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(91, 25);
            this.label7.TabIndex = 17;
            this.label7.Text = "behaviour";
            // 
            // delete_button
            // 
            this.delete_button.Location = new System.Drawing.Point(1059, 250);
            this.delete_button.Name = "delete_button";
            this.delete_button.Size = new System.Drawing.Size(112, 34);
            this.delete_button.TabIndex = 19;
            this.delete_button.Text = "Delete";
            this.delete_button.UseVisualStyleBackColor = true;
            this.delete_button.Click += new System.EventHandler(this.delete_button_Click);
            // 
            // update_button
            // 
            this.update_button.Location = new System.Drawing.Point(1239, 250);
            this.update_button.Name = "update_button";
            this.update_button.Size = new System.Drawing.Size(112, 34);
            this.update_button.TabIndex = 20;
            this.update_button.Text = "Update";
            this.update_button.UseVisualStyleBackColor = true;
            this.update_button.Click += new System.EventHandler(this.update_button_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1432, 529);
            this.Controls.Add(this.update_button);
            this.Controls.Add(this.delete_button);
            this.Controls.Add(this.behaviour_box);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.color_box);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.fweight_box);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.add_button);
            this.Controls.Add(this.flength_box);
            this.Controls.Add(this.sname_box);
            this.Controls.Add(this.name_box);
            this.Controls.Add(this.id_box);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGridView2);
            this.Controls.Add(this.dataGridView1);
            this.Controls.Add(this.connect_button);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button connect_button;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridView dataGridView2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox id_box;
        private System.Windows.Forms.TextBox name_box;
        private System.Windows.Forms.TextBox sname_box;
        private System.Windows.Forms.TextBox flength_box;
        private System.Windows.Forms.Button add_button;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox fweight_box;
        private System.Windows.Forms.TextBox color_box;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox behaviour_box;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button delete_button;
        private System.Windows.Forms.Button update_button;
    }
}

