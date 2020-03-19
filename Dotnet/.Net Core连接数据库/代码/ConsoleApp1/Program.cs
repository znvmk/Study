using System;
using System.Collections.Generic;
using System.Data.Entity.Infrastructure;
using System.Data.Entity.Migrations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ConsoleApp1.Models;

namespace ConsoleApp1
{
    class Program
    {
        private static string connectionStr = "Server=WU-PC;Database=Test;user id=sa;Password =123456;MultipleActiveResultSets=true";
        private static string connectionMySQLStr = "Server=localhost;Database=test;uid=root;pwd=123456;";
        private static IRepository<User> repo;
        private static bool useMySQl = true;
        static void Main(string[] args)
        {
            // 创建SQL数据库
            MigrateDb();
            // 创建MySQL数据库
            MigrateMySQLDb();
            // 选择 repository
            if (useMySQl)
            {
                repo = new MySQLRepository();
            }
            else
            {
                repo = new SQLRepository(connectionStr);
            }
            // 使用 repository
            using (repo)
            {

                repo.Create(new User { UserName = "Test", Gender = "Test" });
                repo.Save();
                foreach (var u in repo.GetAll())
                {
                    //Console.WriteLine($"{u.UserId}.{u.UserName} - {u.Gender}");
                    Console.WriteLine(string.Format("{0}.{1} - {2}", u.UserId, u.UserName, u.Gender));
                }
            }
            Console.Read();
        }
        public static void MigrateDb()
        {
            var configuration = new Configuration();
            configuration.TargetDatabase = new DbConnectionInfo(connectionStr, "System.Data.SqlClient");
            var migrator = new DbMigrator(configuration);
            migrator.Update();
        }
        public static void MigrateMySQLDb()
        {
            var configuration = new MySQLConfiguration();
            configuration.TargetDatabase = new DbConnectionInfo(connectionMySQLStr, "MySql.Data.MySqlClient");
            var migrator = new DbMigrator(configuration);
            migrator.Update();
        }
    }
}