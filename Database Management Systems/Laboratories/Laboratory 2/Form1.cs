/*
 *App.config file
<?xml version="1.0" encoding="utf-8" ?>
<configuration>
	<connectionStrings>
		<add name= "cn" connectionString="Data Source=DESKTOP-0ACD0H5\SQLEXPRESS;Initial Catalog=OceanLife;Integrated Security=True"/>
	</connectionStrings>

	<startup>
		<supportedRuntime version="v4.0" sku=".NETFramework,Version=v4.5.2" />
	</startup>

	<!--
	<appSettings>
		<add key= "select_parent" value="Select * from Species" />
		<add key= "select_child" value="Select * from LivingBeing where Sname = @s" />
		<add key= "parent_table_name" value="Species" />
		<add key= "parent_id" value="name" />
		<add key= "child_parent_key" value="Sname" />
		<add key= "child_id_name" value="id" />
		<add key= "child_table_name" value="LivingBeing" />
		<add key= "child_no_of_columns" value="7" />
		<add key= "child_column_names" value= "id,name,Sname,fLength,fWeight,color,behaviour"/>
		<add key= "column_names_insert_parameters" value="@id,@name,@Sname,@fLength,@fWeight,@color,@behaviour" />
		<add key= "update_query" value="UPDATE LivingBeing SET name=@name, fLength=@flength, fWeight=@fWeight, color=@color, behaviour=@behaviour WHERE id=@id" />
	</appSettings>
	-->
	

	<appSettings>
		<add key= "select_parent" value="Select * from Families" />
		<add key= "select_child" value="Select * from Genera where Fname=@s" />
		<add key= "parent_table_name" value="Families" />
		<add key= "parent_id" value="name" />
		<add key= "child_parent_key" value="Fname" />
		<add key= "child_id_name" value="name" />
		<add key= "child_table_name" value="Genera" />
		<add key= "child_no_of_columns" value="3" />
		<add key= "child_column_names" value= "name,Fname,speciesCount"/>
		<add key= "column_names_insert_parameters" value="@name,@Fname,@speciesCount" />
		<add key= "update_query" value="UPDATE Genera SET Fname=@Fname, speciesCount=@speciesCount WHERE name=@name" />
	</appSettings>

</configuration>
 */

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
using System.Configuration;
using System.Diagnostics;

namespace Lab2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        
        private void insert_button_Click(object sender, EventArgs e)
        {
            
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            SqlConnection cs = new SqlConnection(con);
            SqlDataAdapter da = new SqlDataAdapter();
            DataSet ds = new DataSet();

            try
            {
                string child_table_name = ConfigurationManager.AppSettings["child_table_name"];
                string child_column_names = ConfigurationManager.AppSettings["child_column_names"];
                string column_names_insert_parameters = ConfigurationManager.AppSettings["column_names_insert_parameters"];
                List<string> column_names_list = new List<string>(ConfigurationManager.AppSettings["child_column_names"].Split(','));
                SqlCommand cmd = new SqlCommand("INSERT INTO " + child_table_name + " (" + child_column_names + ") Values (" + column_names_insert_parameters + ")", cs);
                foreach (string column in column_names_list)
                {
                    TextBox textBox = (TextBox)panel1.Controls[column];
                    cmd.Parameters.AddWithValue("@" + column, textBox.Text);
                }
                cs.Open();
                cmd.ExecuteNonQuery();
                MessageBox.Show("Inserted Succesfull to the Database");
                cs.Close();
                string child_parent_key = ConfigurationManager.AppSettings["child_parent_key"];
                string select_child = ConfigurationManager.AppSettings["select_child"];
                da.SelectCommand = new SqlCommand(select_child, cs);
                TextBox textBox1 = (TextBox)panel1.Controls[child_parent_key];
                da.SelectCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = textBox1.Text;
                ds.Clear();
                da.Fill(ds);
                dataGridView2.DataSource = ds.Tables[0];
            }
            catch (Exception ex) {
                MessageBox.Show(ex.ToString());
                cs.Close();
            }


        }

        private void delete_button_Click(object sender, EventArgs e)
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            SqlConnection cs = new SqlConnection(con);
            SqlDataAdapter da = new SqlDataAdapter();
            DataSet ds = new DataSet();
            try
            {
                DialogResult dr;
                dr = MessageBox.Show("Are you sure?", "Confirm Deletion", MessageBoxButtons.YesNo);
                if (dr == DialogResult.Yes)
                {
                    string child_table = ConfigurationManager.AppSettings["child_table_name"];
                    string child_id = ConfigurationManager.AppSettings["child_id_name"];
                    da.DeleteCommand = new SqlCommand("DELETE FROM " + child_table + " WHERE " + child_id + "=@" + child_id, cs);
                    TextBox textBox2 = (TextBox)panel1.Controls[child_id];
                    Debug.WriteLine(textBox2.Text);
                    da.DeleteCommand.Parameters.AddWithValue("@" + child_id, textBox2.Text);

                    cs.Open();
                    da.DeleteCommand.ExecuteNonQuery();
                    cs.Close();
                    MessageBox.Show("Succesfull Deletion");
                    string child_parent_key = ConfigurationManager.AppSettings["child_parent_key"];
                    string select_child = ConfigurationManager.AppSettings["select_child"];
                    da.SelectCommand = new SqlCommand(select_child, cs);
                    TextBox textBox1 = (TextBox)panel1.Controls[child_parent_key];
                    da.SelectCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = textBox1.Text;
                    ds.Clear();
                    da.Fill(ds);
                    dataGridView2.DataSource = ds.Tables[0];
                }
                else
                {
                    MessageBox.Show("Deletion Aborded");
                }

            }
            catch (Exception ex) {
                MessageBox.Show(ex.ToString());
                cs.Close();
            }

        }

        private void update_button_Click(object sender, EventArgs e)
        {
            string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
            SqlConnection cs = new SqlConnection(con);
            SqlDataAdapter da = new SqlDataAdapter();
            DataSet ds = new DataSet();
            try
            {
                int x;
                string update_query = ConfigurationManager.AppSettings["update_query"];
                da.UpdateCommand = new SqlCommand(update_query, cs);

                string child_table_name = ConfigurationManager.AppSettings["child_table_name"];
                string child_column_names = ConfigurationManager.AppSettings["child_column_names"];
                string column_names_insert_parameters = ConfigurationManager.AppSettings["column_names_insert_parameters"];
                List<string> column_names_list = new List<string>(ConfigurationManager.AppSettings["child_column_names"].Split(','));
                foreach (string column in column_names_list)
                {
                    TextBox textBox = (TextBox)panel1.Controls[column];
                    da.UpdateCommand.Parameters.AddWithValue("@" + column, textBox.Text);
                }
                cs.Open();
                x = da.UpdateCommand.ExecuteNonQuery();
                cs.Close();
                if (x >= 1) {
                    MessageBox.Show("The record has been updated");
                    string child_parent_key = ConfigurationManager.AppSettings["child_parent_key"];
                    string select_child = ConfigurationManager.AppSettings["select_child"];
                    da.SelectCommand = new SqlCommand(select_child, cs);
                    TextBox textBox1 = (TextBox)panel1.Controls[child_parent_key];
                    da.SelectCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = textBox1.Text;
                    ds.Clear();
                    da.Fill(ds);
                    dataGridView2.DataSource = ds.Tables[0];
                }
            }
            catch (Exception ex) {
                MessageBox.Show(ex.ToString());
                cs.Close();
            }
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (e.RowIndex >= 0)
                {
                    DataGridViewRow row = dataGridView1.Rows[e.RowIndex];

                    string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
                    SqlConnection cs = new SqlConnection(con);
                    SqlDataAdapter da = new SqlDataAdapter();
                    DataSet ds = new DataSet();
                    string select_child = ConfigurationManager.AppSettings["select_child"];
                    da.SelectCommand = new SqlCommand(select_child, cs);
                    da.SelectCommand.Parameters.Add("@s", SqlDbType.VarChar).Value = row.Cells[0].Value.ToString();
                    ds.Clear();
                    da.Fill(ds);

                    dataGridView2.DataSource = ds.Tables[0];
                    //sname_box.Text = row.Cells[0].Value.ToString();
                }
            }
            catch (Exception ex) {
                MessageBox.Show(ex.ToString());
            }
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                if (e.RowIndex >= 0)
                {
                    List<string> column_names = new List<string>(ConfigurationManager.AppSettings["child_column_names"].Split(','));
                    DataGridViewRow row = dataGridView2.Rows[e.RowIndex];

                    int i = 0;
                    foreach (string column in column_names)
                    {
                        TextBox textBox = (TextBox)panel1.Controls[column];
                        textBox.Text = row.Cells[i].Value.ToString();
                        i++;
                    }

                }
            }
            catch (Exception ex) {
                MessageBox.Show(ex.ToString());
            }
        }

        private void connect_button_Click(object sender, EventArgs e)
        {
            try
            {
                string con = ConfigurationManager.ConnectionStrings["cn"].ConnectionString;
                SqlConnection cs = new SqlConnection(con);
                SqlDataAdapter da = new SqlDataAdapter();
                DataSet ds = new DataSet();
                string select_parent = ConfigurationManager.AppSettings["select_parent"];
                da.SelectCommand = new SqlCommand(select_parent, cs);
                ds.Clear();
                da.Fill(ds);
                dataGridView1.DataSource = ds.Tables[0];
            }
            catch (Exception ex) {
                MessageBox.Show(ex.ToString());
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                List<string> column_names = new List<string>(ConfigurationManager.AppSettings["child_column_names"].Split(','));
                int pointX = 30;
                int pointY = 40;
                int number_of_cols = Convert.ToInt32(ConfigurationManager.AppSettings["child_no_of_columns"]);
                panel1.Controls.Clear();
                foreach (string col in column_names) {
                    TextBox a = new TextBox();
                    a.Text = col;
                    a.Name = col;
                    a.Location = new Point(pointX, pointY);
                    a.Visible = true;
                    a.Parent = panel1;
                    panel1.Show();
                    pointY += 30;
                }
            }
            catch (Exception ex) {
                MessageBox.Show(ex.ToString());
            }
        }
    }
}
