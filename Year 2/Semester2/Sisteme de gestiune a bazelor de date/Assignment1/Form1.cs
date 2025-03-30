using System;
using System.Data;
using System.Windows.Forms;
using System.Data.SqlClient;



namespace DBMS_Lab1_pt2
{
    public partial class Form1: Form
    {
        SqlConnection conn;
        SqlDataAdapter daProducer; //for the paretn table
        SqlDataAdapter daBrand; // for the child table  
        DataSet dset;
        BindingSource bsProducer;
        BindingSource bsBrand;
        SqlCommandBuilder cmdBuilder;
        string queryProducer;
        string queryBrand;
        public Form1()
        {
            InitializeComponent();
            FillData();
        }

        void FillData()
        {

            try
            {
                conn = new SqlConnection(getConnectionString());
            }
            catch(SystemException)
            {
                Console.WriteLine("Connection failed");
            }

            queryProducer = "SELECT * FROM Producer";
            queryBrand = "SELECT * FROM Brand";

            daProducer = new SqlDataAdapter(queryProducer, conn);
            daBrand = new SqlDataAdapter(queryBrand, conn);
            dset = new DataSet();
            try
            {
                daBrand.Fill(dset, "Brand");
                daProducer.Fill(dset, "Producer");
            }
            catch (SystemException)
            {
                Console.WriteLine("Data filling failed");
            }

            cmdBuilder = new SqlCommandBuilder(daBrand);
            dset.EnforceConstraints = false;
            dset.Relations.Add("ProducerBrand", dset.Tables["Producer"].Columns["producerID"], dset.Tables["Brand"].Columns["producerID"]);

            bsProducer = new BindingSource();
            bsProducer.DataSource = dset.Tables["Producer"];
            bsBrand = new BindingSource(bsProducer, "ProducerBrand");

            this.dataGridView1.DataSource = bsProducer;
            this.dataGridView2.DataSource = bsBrand;


            cmdBuilder.GetUpdateCommand();
        }

        string getConnectionString() {
            return "Data Source=leptop-sarici;Initial Catalog=SneakerStore2;" + "Integrated Security=true;";

        }

      

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                daBrand.Update(dset, "Brand");
            }
            catch (SystemException)
            {
                Console.WriteLine("Update failed");
            }
        }
    }
}
