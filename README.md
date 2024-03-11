测试一下git 的一些命令


```
git --help  #查看git的命令
git status #查看工作区和暂存区有什么区别
git add .  将代码从工作区增加到本地
git commit -m "提交说明"  提交到本地 
git pull    ---  拉取远程代码
git push -u origin master 
```

从github网站上修改的readme文件

* 学习git 关联远程仓库 

  ```
  git init //把这个目录变成Git可以管理的仓库
  　　git add README.md //文件添加到仓库
  　　git add . //不但可以跟单一文件，还可以跟通配符，更可以跟目录。一个点就把当前目录下所有未追踪的文件全部add了 
  　　git commit -m "first commit" //把文件提交到仓库
  　　git remote add origin git@github.com:wangjiax9/practice.git //关联远程仓库
  　　git push -u origin master //把本地库的所有内容推送到远程库上
  ```

  

* 学习 git 冲突解决方法——定位到冲突文件，删除掉冲突标识符号

* 理解 git 分支

  ​	git checkout -b dev //创建dev分支并且转换到dev分支 == git switch -c dev

  [Git系列教程(四)——git分支管理_git publish-CSDN博客](https://blog.csdn.net/qq_47183158/article/details/123642048?ops_request_misc=%7B%22request%5Fid%22%3A%22170912711916800185823335%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=170912711916800185823335&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-123642048-null-null.142^v99^pc_search_result_base5&utm_term=git分支管理&spm=1018.2226.3001.4187)

  ​	

* git 回退

  ``` git
  git checkout -- [文件名]
  git reset HEAD [文件名]
  ```

  

  

* git 相关开发工具

  可视化工具

  	* sourcetree
  	* 小乌龟