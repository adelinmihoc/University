using System;
using System.Threading.Tasks;
using MySqlConnector;
using System.Data;
using System.Data.Common;
using System.Collections.Generic;

 
namespace asp_project.Models
{
    public class DbUtil
    {
        internal AppDb Db { get; set; }
        public DbUtil()
        {
            
        }
        internal DbUtil(AppDb db)
        {
            Db = db;
        }

        public async Task InsertAsync(Entity body)
        {

            using var cmd = Db.Connection.CreateCommand();
            cmd.CommandText = @"insert into movies (title, genre) values (@title, @genre);";
            // cmd.Parameters.Add(new MySqlParameter
            // {
            //     ParameterName = "@title",
            //     DbType = DbType.String,
            //     Value = body.title
            // });
            // cmd.Parameters.Add(new MySqlParameter
            // {
            //     ParameterName = "@genre",
            //     DbType = DbType.String,
            //     Value = body.genre
            // });

            await cmd.ExecuteNonQueryAsync();

        }

        public async Task UpdateAsync(Entity body)
        {
            using var cmd = Db.Connection.CreateCommand();
            cmd.CommandText = @"update movies set title = @title, genre = @genre where id = @id";
            // cmd.Parameters.Add(new MySqlParameter
            // {
            //     ParameterName = "@title",
            //     DbType = DbType.String,
            //     Value = body.title
            // });
            // cmd.Parameters.Add(new MySqlParameter
            // {
            //     ParameterName = "@genre",
            //     DbType = DbType.String,
            //     Value = body.genre
            // });
            // cmd.Parameters.Add(new MySqlParameter
            // {
            //     ParameterName = "@id",
            //     DbType = DbType.Int32,
            //     Value = body.id
            // });

            await cmd.ExecuteNonQueryAsync();
        }

        public async Task DeleteAsync(Entity body)
        {
            using var cmd = Db.Connection.CreateCommand();
            cmd.CommandText = @"delete from movies where id = @id";
            cmd.Parameters.Add(new MySqlParameter
            {
                ParameterName = "@id",
                DbType = DbType.Int32,
                Value = body.id
            });
            await cmd.ExecuteNonQueryAsync();
        }

        // public async Task<Entity> FindOneAsync(Entity body)
        // {
        //     using var cmd = Db.Connection.CreateCommand();
        //     cmd.CommandText = @"select * from posts where id = @id";
        //     cmd.Parameters.Add(new MySqlParameter
        //     {
        //         ParameterName = "@id",
        //         DbType = DbType.Int32,
        //         Value = body.id
        //     });
        //     var result = await ReadAllAsync2(await cmd.ExecuteReaderAsync());
        //     return result.Count > 0 ? result[0] : null;
        // }

        // public async Task<List<Entity>> FindAllAsync() 
        // {
        //     using var cmd = Db.Connection.CreateCommand();
        //     cmd.CommandText = @"select * from files;";
        //     return await ReadAllAsync2(await cmd.ExecuteReaderAsync());
        // }

        public async Task<List<Entity>> FindAllAsync2(Entity body) 
        {
            using var cmd = Db.Connection.CreateCommand();
            cmd.CommandText = @"select * from files f where f.filecontent like concat('% ', @word, ' %');";
            cmd.Parameters.Add(new MySqlParameter
            {
                ParameterName = "@word",
                DbType = DbType.String,
                Value = body.word
            });
            return await ReadAllAsync(await cmd.ExecuteReaderAsync(), body.word);
        }

        private async Task<List<Entity>> ReadAllAsync(DbDataReader reader, string word)
        {
            var entities = new List<Entity>();
            using (reader)
            {
                while (await reader.ReadAsync())
                {
                    var entity = new Entity()
                    {
                        id = reader.GetInt32(0),
                        userid = reader.GetInt32(1),
                        filename = reader.GetString(2),
                        filecontent = reader.GetString(3),
                        size = reader.GetInt32(4),
                    };

                    string[] contents = entity.filecontent.Split(' ');
                    var count = 0;
                    foreach (var s in contents) 
                    {
                        if (s == word)
                        {
                            count++;
                        }
                    }
                    entity.apparitions = count;
                    entities.Add(entity);
                }
            }
            return entities;
        }

        

        private async Task<List<Entity>> ReadAllAsync3(DbDataReader reader)
        {
            var entities = new List<Entity>();
            using (reader)
            {
                while (await reader.ReadAsync())
                {
                    var entity = new Entity()
                    {
                        username = reader.GetString(0),
                        password = reader.GetString(1),
                    };
                    entities.Add(entity);
                }
            }
            return entities;
        }

        public async Task<Entity> AuthenticateAsync(Entity body)
        {
            using var cmd = Db.Connection.CreateCommand();
            cmd.CommandText = @"select u.username, u.password from users u inner join files f on u.id = f.userid where u.username = @username and u.password = @password and f.size = @size;";
            cmd.Parameters.Add(new MySqlParameter
            {
                ParameterName = "@username",
                DbType = DbType.String,
                Value = body.username
            });
            cmd.Parameters.Add(new MySqlParameter
            {
                ParameterName = "@password",
                DbType = DbType.String,
                Value = body.password
            });
            cmd.Parameters.Add(new MySqlParameter
            {
                ParameterName = "@size",
                DbType = DbType.String,
                Value = body.size
            });
            var result = await ReadAllAsync3(await cmd.ExecuteReaderAsync());
            return result.Count > 0 ? result[0] : null;
        }

         public async Task RegisterAsync(Entity body)
        {
            using var cmd = Db.Connection.CreateCommand();
            cmd.CommandText = @"insert ignore into users (username, password) values (@username, @password);";
            cmd.Parameters.Add(new MySqlParameter
            {
                ParameterName = "@username",
                DbType = DbType.String,
                Value = body.username
            });
            cmd.Parameters.Add(new MySqlParameter
            {
                ParameterName = "@password",
                DbType = DbType.String,
                Value = body.password
            });
            await cmd.ExecuteNonQueryAsync();
        }

    } // class

} // namespace
