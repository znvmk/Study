
using Microsoft.EntityFrameworkCore;

namespace ConsoleApp2.Model
{
    public class MansContext :DbContext
    {
        public DbSet<Man> Man { get; set; }
        //public DbSet<Post> Post { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            //配置mariadb连接字符串
            // optionsBuilder.UseMySql("Server=localhost;Port=3306;Database=BloggingDB; User=root;Password=;");
            optionsBuilder.UseSqlServer("Server=DESKTOP-L6H201M\\SQLEXPRESS;Database=wer;Trusted_Connection=True;MultipleActiveResultSets=true");
        }
    }
}