using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Lab1
{
    public partial class Form1 : Form
    {
        private String connectionString = "Data Source=DESKTOP-0ACD0H5\\SQLEXPRESS;Initial Catalog=OceanLife;Integrated Security=True";

        public Form1()
        {
            InitializeComponent();
        }

        private void connect_button_Click(object sender, EventArgs e)
        {
            SqlConnection cs = new SqlConnection(this.connectionString);
            SqlDataAdapter da = new SqlDataAdapter();
            DataSet ds = new DataSet();
            da.SelectCommand = new SqlCommand("Select * from Species", cs);
            ds.Clear();
            da.Fill(ds);
            dataGridView1.DataSource = ds.Tables[0];
        }

        private void add_button_Click(object sender, EventArgs e)
        {
            SqlConnection cs = new SqlConnection(this.connectionString);
            SqlDataAdapter da = new SqlDataAdapter();
            DataSet ds = new DataSet();

            try
            {
                da.InsertCommand = new SqlCommand("INSERT INTO LivingBeing (id, name, Sname, fLength, fWeight, color, behaviour) VALUES (@p1, @p2, @p3, @p4, @p5, @p6, @p7)", cs);
                da.InsertCommand.Parameters.Add("@p1", SqlDbType.Int).Value = Int32.Parse(id_box.Text);
                da.InsertCommand.Parameters.Add("@p2", SqlDbType.VarChar).Value = name_box.Text;
                da.InsertCommand.Parameters.Add("@p3", SqlDbType.VarChar).Value = sname_box.Text;
                da.InsertCommand.Parameters.Add("@p4", SqlDbType.Float).Value = float.Parse(flength_box.Text);
                da.InsertCommand.Parameters.Add("@p5", SqlDbType.Float).Value = float.Parse(fweight_box.Text);
                da.InsertCommand.Parameters.Add("@p6", SqlDbType.Char).Value = color_box.Text;
                da.InsertCommand.Parameters.Add("@p7", SqlDbType.VarChar).Value = behaviour_box.Text;

                cs.Open();
                da.InsertCommand.ExecuteNonQuery();
                MessageBox.Show("Inserted Succesfull to the Database");
                cs.Close();
                da.SelectCommand = new SqlCommand("SELECT * FROM LivingBeing WHERE Sname = @s", cs);
                da.SelectCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = sname_box.Text;
                ds.Clear();
                da.Fill(ds);
                dataGridView2.DataSource = ds.Tables[0];
            }
            catch (Exception ex) {
                MessageBox.Show(ex.Message);
                cs.Close();
            }
           

        }
        private void delete_button_Click(object sender, EventArgs e)
        {
            SqlConnection cs = new SqlConnection(this.connectionString);
            SqlDataAdapter da = new SqlDataAdapter();
            DataSet ds = new DataSet();

            try {
                DialogResult dr;
                dr = MessageBox.Show("Are you sure?", "Confirm Deletion", MessageBoxButtons.YesNo);
                if (dr == DialogResult.Yes)
                {
                    da.DeleteCommand = new SqlCommand("DELETE FROM LivingBeing where id=@id", cs);
                    da.DeleteCommand.Parameters.Add("@id", SqlDbType.Int).Value = Int32.Parse(id_box.Text);

                    cs.Open();
                    da.DeleteCommand.ExecuteNonQuery();
                    cs.Close();
                    MessageBox.Show("Succesfull Deletion");
                    da.SelectCommand = new SqlCommand("SELECT * FROM LivingBeing WHERE Sname = @s", cs);
                    da.SelectCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = sname_box.Text;
                    ds.Clear();
                    da.Fill(ds);
                    dataGridView2.DataSource = ds.Tables[0];
                }
                else
                {
                    MessageBox.Show("Deletion Aborded");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                cs.Close();
            }
            
        }

        private void update_button_Click(object sender, EventArgs e)
        {
            SqlConnection cs = new SqlConnection(this.connectionString);
            SqlDataAdapter da = new SqlDataAdapter();
            DataSet ds = new DataSet();

            try {
                int x;
                da.UpdateCommand = new SqlCommand("UPDATE LivingBeing set name=@p2, Sname=@p3, fLength=@p4, fWeight=@p5, color=@p6, behaviour=@p7 WHERE id=@p1", cs);
                da.UpdateCommand.Parameters.Add("@p1", SqlDbType.Int).Value = Int32.Parse(id_box.Text);
                da.UpdateCommand.Parameters.Add("@p2", SqlDbType.VarChar).Value = name_box.Text;
                da.UpdateCommand.Parameters.Add("@p3", SqlDbType.VarChar).Value = sname_box.Text;
                da.UpdateCommand.Parameters.Add("@p4", SqlDbType.Float).Value = float.Parse(flength_box.Text);
                da.UpdateCommand.Parameters.Add("@p5", SqlDbType.Float).Value = float.Parse(fweight_box.Text);
                da.UpdateCommand.Parameters.Add("@p6", SqlDbType.Char).Value = color_box.Text;
                da.UpdateCommand.Parameters.Add("@p7", SqlDbType.VarChar).Value = behaviour_box.Text;

                cs.Open();
                x = da.UpdateCommand.ExecuteNonQuery();
                cs.Close();
                if (x >= 1)
                {
                    MessageBox.Show("The record has been updated");
                }
                da.SelectCommand = new SqlCommand("SELECT * FROM LivingBeing WHERE Sname = @s", cs);
                da.SelectCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = sname_box.Text;
                ds.Clear();
                da.Fill(ds);
                dataGridView2.DataSource = ds.Tables[0];
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                cs.Close();
            }
            
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0)
            {
                DataGridViewRow row = dataGridView1.Rows[e.RowIndex];

                SqlConnection cs = new SqlConnection(this.connectionString);
                SqlDataAdapter da = new SqlDataAdapter();
                DataSet ds = new DataSet();
                da.SelectCommand = new SqlCommand("SELECT * FROM LivingBeing WHERE Sname = @s", cs);
                da.SelectCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = row.Cells[0].Value.ToString();
                ds.Clear();
                da.Fill(ds);

                dataGridView2.DataSource = ds.Tables[0];
                sname_box.Text = row.Cells[0].Value.ToString();

            }
           

            
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex >= 0) {
                DataGridViewRow row = dataGridView2.Rows[e.RowIndex];
                id_box.Text = row.Cells[0].Value.ToString();
                name_box.Text = row.Cells[1].Value.ToString();
                sname_box.Text = row.Cells[2].Value.ToString();
                flength_box.Text = row.Cells[3].Value.ToString();
                fweight_box.Text = row.Cells[4].Value.ToString();
                color_box.Text = row.Cells[5].Value.ToString();
                behaviour_box.Text = row.Cells[6].Value.ToString();
            }


        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

    }
}
