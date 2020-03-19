using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;



namespace ConsoleApp1.Models
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(string connectionString)
            : base(connectionString)
        {

        }
        public DbSet<User> Users { get; set; }
    }
}
